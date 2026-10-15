#include "polynomial_regression.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

Vector<Vector<double>> computeNormalEquations(const Vector<Vector<double>>& x)
{
    if (x.size() == 0 || x.get(0).size() == 0)
        throw invalid_argument("X must not be empty.");

    int columns = x.get(0).size();
    Vector<Vector<double>> result(columns);
    for (int i = 0; i < columns; ++i)
        result.set(i, Vector<double>(columns));

    for (int row = 0; row < x.size(); ++row)
    {
        if (x.get(row).size() != columns)
            throw invalid_argument("All rows of X must have the same size.");

        for (int i = 0; i < columns; ++i)
            for (int j = 0; j < columns; ++j)
                result.get(i).set(j, result.get(i).get(j)
                    + x.get(row).get(i) * x.get(row).get(j));
    }
    return result;
}

Vector<double> fitOLS(const Vector<Vector<double>>& x, const Vector<double>& y)
{
    if (x.size() != y.size())
        throw invalid_argument("X and y must have the same number of rows.");

    Vector<Vector<double>> matrix = computeNormalEquations(x);
    int n = matrix.size();
    Vector<double> values(n);

    for (int row = 0; row < x.size(); ++row)
        for (int column = 0; column < n; ++column)
            values.set(column, values.get(column)
                + x.get(row).get(column) * y.get(row));

    // Solve (X^T X) * coefficients = X^T y.
    for (int pivot = 0; pivot < n; ++pivot)
    {
        int best = pivot;
        for (int row = pivot + 1; row < n; ++row)
            if (abs(matrix.get(row).get(pivot)) >
                abs(matrix.get(best).get(pivot)))
                best = row;

        if (abs(matrix.get(best).get(pivot)) < 1e-12)
            throw runtime_error("The normal-equation matrix is singular.");

        swap(matrix.get(pivot), matrix.get(best));
        swap(values.get(pivot), values.get(best));

        for (int row = pivot + 1; row < n; ++row)
        {
            double factor = matrix.get(row).get(pivot)
                / matrix.get(pivot).get(pivot);
            for (int column = pivot; column < n; ++column)
                matrix.get(row).set(column, matrix.get(row).get(column)
                    - factor * matrix.get(pivot).get(column));
            values.set(row, values.get(row) - factor * values.get(pivot));
        }
    }

    Vector<double> coefficients(n);
    for (int row = n; row-- > 0;)
    {
        double value = values.get(row);
        for (int column = row + 1; column < n; ++column)
            value -= matrix.get(row).get(column) * coefficients.get(column);
        coefficients.set(row, value / matrix.get(row).get(row));
    }
    return coefficients;
}

int main()
{
    Vector<Vector<double>> x(3);
    for (int row = 0; row < 3; ++row)
        x.set(row, Vector<double>(2));
    x.get(0).set(0, 1); x.get(0).set(1, 1);
    x.get(1).set(0, 1); x.get(1).set(1, 2);
    x.get(2).set(0, 1); x.get(2).set(1, 3);
    Vector<double> y(3);
    y.set(0, 3); y.set(1, 5); y.set(2, 7);

    Vector<Vector<double>> xtx = computeNormalEquations(x);
    cout << "X^T X:\n";
    for (int i = 0; i < xtx.size(); ++i)
    {
        for (int j = 0; j < xtx.get(i).size(); ++j)
            cout << xtx.get(i).get(j) << ' ';
        cout << '\n';
    }

    Vector<double> coefficients = fitOLS(x, y);
    cout << "Intercept: " << coefficients.get(0) << '\n';
    cout << "Slope: " << coefficients.get(1) << '\n';
    return 0;
}
