#include "polynomial_regression.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace ols {
using namespace std;

static Vector<Vector<double>> zeros(int rows, int cols)
{
    Vector<Vector<double>> m(rows);
    for (int i = 0; i < rows; ++i)
        m.set(i, Vector<double>(cols));
    return m;
}

static void requireRectangular(const Vector<Vector<double>>& a, const char* name)
{
    if (a.size() == 0 || a.get(0).size() == 0)
        throw invalid_argument(string(name) + " must not be empty.");
    for (int i = 1; i < a.size(); ++i)
        if (a.get(i).size() != a.get(0).size())
            throw invalid_argument(string(name) + " rows must have equal size.");
}

Vector<Vector<double>> transpose(const Vector<Vector<double>>& a)
{
    requireRectangular(a, "Matrix");
    int rows = a.size();
    int cols = a.get(0).size();
    Vector<Vector<double>> t = zeros(cols, rows);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            t.get(j).set(i, a.get(i).get(j));
    return t;
}

Vector<Vector<double>> multiply(const Vector<Vector<double>>& a,
                                const Vector<Vector<double>>& b)
{
    requireRectangular(a, "A");
    requireRectangular(b, "B");
    int m = a.size();
    int n = a.get(0).size();
    int p = b.get(0).size();
    if (b.size() != n)
        throw invalid_argument("Inner dimensions do not match.");

    Vector<Vector<double>> c = zeros(m, p);
    for (int i = 0; i < m; ++i)
        for (int k = 0; k < n; ++k)
        {
            double aik = a.get(i).get(k);
            for (int j = 0; j < p; ++j)
                c.get(i).set(j, c.get(i).get(j) + aik * b.get(k).get(j));
        }
    return c;
}

Vector<double> multiply(const Vector<Vector<double>>& a, const Vector<double>& v)
{
    requireRectangular(a, "A");
    if (a.get(0).size() != v.size())
        throw invalid_argument("Matrix columns must match vector size.");

    Vector<double> result(a.size());
    for (int i = 0; i < a.size(); ++i)
    {
        double sum = 0.0;
        for (int j = 0; j < v.size(); ++j)
            sum += a.get(i).get(j) * v.get(j);
        result.set(i, sum);
    }
    return result;
}

Vector<Vector<double>> inverse(const Vector<Vector<double>>& a)
{
    requireRectangular(a, "Matrix");
    int n = a.size();
    if (a.get(0).size() != n)
        throw invalid_argument("Only square matrices can be inverted.");

    // Relative singularity tolerance: scale by the largest entry of A.
    double scale = 0.0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scale = max(scale, abs(a.get(i).get(j)));

    Vector<Vector<double>> work = zeros(n, 2 * n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            work.get(i).set(j, a.get(i).get(j));
        work.get(i).set(n + i, 1.0);
    }

    for (int pivot = 0; pivot < n; ++pivot)
    {
        int best = pivot;
        for (int row = pivot + 1; row < n; ++row)
            if (abs(work.get(row).get(pivot)) > abs(work.get(best).get(pivot)))
                best = row;

        if (scale == 0.0 || abs(work.get(best).get(pivot)) <= 1e-12 * scale)
            throw runtime_error("The matrix is singular and cannot be inverted.");

        swap(work.get(pivot), work.get(best));

        double diag = work.get(pivot).get(pivot);
        for (int col = 0; col < 2 * n; ++col)
            work.get(pivot).set(col, work.get(pivot).get(col) / diag);

        for (int row = 0; row < n; ++row)
        {
            if (row == pivot) continue;
            double factor = work.get(row).get(pivot);
            if (factor == 0.0) continue;
            for (int col = 0; col < 2 * n; ++col)
                work.get(row).set(col,
                    work.get(row).get(col) - factor * work.get(pivot).get(col));
        }
    }

    Vector<Vector<double>> inv = zeros(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inv.get(i).set(j, work.get(i).get(n + j));
    return inv;
}

Vector<Vector<double>> computeNormalEquations(const Vector<Vector<double>>& x)
{
    requireRectangular(x, "X");
    Vector<Vector<double>> xt = transpose(x);
    return multiply(xt, x);
}

Vector<double> computeXtY(const Vector<Vector<double>>& x, const Vector<double>& y)
{
    if (x.size() != y.size())
        throw invalid_argument("X and y must have the same number of rows.");
    return multiply(transpose(x), y);
}

Vector<double> fitOLS(const Vector<Vector<double>>& x, const Vector<double>& y)
{
    requireRectangular(x, "X");
    if (x.size() != y.size())
        throw invalid_argument("X and y must have the same number of rows.");
    if (x.size() < x.get(0).size())
        throw invalid_argument("Need at least as many samples as coefficients.");

    Vector<Vector<double>> xtx = computeNormalEquations(x);
    Vector<Vector<double>> xtxInverse = inverse(xtx);
    Vector<double> xty = computeXtY(x, y);
    return multiply(xtxInverse, xty);
}

Vector<Vector<double>> makeDesignMatrix(const Vector<double>& t, int degree)
{
    if (degree < 0)
        throw invalid_argument("Degree must be non-negative.");
    Vector<Vector<double>> x = zeros(t.size(), degree + 1);
    for (int i = 0; i < t.size(); ++i)
    {
        double power = 1.0;
        for (int d = 0; d <= degree; ++d)
        {
            x.get(i).set(d, power);
            power *= t.get(i);
        }
    }
    return x;
}

Vector<double> fitPolynomial(const Vector<double>& t, const Vector<double>& y,
                             int degree)
{
    return fitOLS(makeDesignMatrix(t, degree), y);
}

double predict(const Vector<double>& beta, double t)
{
    double result = 0.0;
    for (int i = beta.size(); i-- > 0;)
        result = result * t + beta.get(i);
    return result;
}

} // namespace ols

#ifdef POLY_REG_DEMO
int main()
{
    using namespace ols;

    Vector<double> t(5), y(5);
    for (int i = 0; i < 5; ++i)
    {
        t.set(i, i);
        y.set(i, 1 + 2.0 * i + 0.5 * i * i);
    }

    Vector<Vector<double>> x = makeDesignMatrix(t, 2);
    Vector<Vector<double>> xtx = computeNormalEquations(x);
    std::cout << "X^T X:\n";
    for (int i = 0; i < xtx.size(); ++i)
    {
        for (int j = 0; j < xtx.get(i).size(); ++j)
            std::cout << xtx.get(i).get(j) << ' ';
        std::cout << '\n';
    }

    Vector<double> beta = fitOLS(x, y);
    for (int i = 0; i < beta.size(); ++i)
        std::cout << "beta[" << i << "] = " << beta.get(i) << '\n';
    std::cout << "predict(5) = " << predict(beta, 5) << " (expected 23.5)\n";
    return 0;
}
#endif /* POLY_REG_DEMO */