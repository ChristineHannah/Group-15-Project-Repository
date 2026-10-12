#include "poly_reg/matrix.hpp"
#include <cmath>
#include <algorithm>

namespace poly_reg {

Matrix::Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {}

Matrix::Matrix(const std::vector<std::vector<double>>& values) 
    : rows(values.size()), cols(values.empty() ? 0 : values[0].size()), data(values) {}

double& Matrix::at(int r, int c) {
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        throw std::out_of_range("Matrix index out of bounds.");
    return data[r][c];
}

double Matrix::at(int r, int c) const {
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        throw std::out_of_range("Matrix index out of bounds.");
    return data[r][c];
}

Matrix Matrix::identity(int n) {
    Matrix id(n, n);
    for (int i = 0; i < n; ++i) {
        id.at(i, i) = 1.0;
    }
    return id;
}

// Determinant Calculation using Gaussian Elimination with Partial Pivoting
double Matrix::determinant() const {
    if (rows != cols) {
        throw std::invalid_argument("Determinant requires a square matrix.");
    }

    int n = rows;
    Matrix mat = *this;
    double det = 1.0;
    const double EPSILON = 1e-9;

    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(mat.at(j, i)) > std::abs(mat.at(pivot, i))) {
                pivot = j;
            }
        }

        if (std::abs(mat.at(pivot, i)) < EPSILON) {
            return 0.0; // Singular matrix
        }

        if (pivot != i) {
            std::swap(mat.data[i], mat.data[pivot]);
            det = -det;
        }

        det *= mat.at(i, i);

        for (int j = i + 1; j < n; ++j) {
            double factor = mat.at(j, i) / mat.at(i, i);
            for (int k = i; k < n; ++k) {
                mat.at(j, k) -= factor * mat.at(i, k);
            }
        }
    }

    return det;
}

// Rank Calculation Helper
int Matrix::rank() const {
    Matrix mat = *this;
    int r = rows;
    int c = cols;
    int rankVal = 0;
    const double EPSILON = 1e-9;

    for (int col = 0, row = 0; col < c && row < r; ++col) {
        int sel = row;
        for (int i = row; i < r; ++i) {
            if (std::abs(mat.at(i, col)) > std::abs(mat.at(sel, col))) {
                sel = i;
            }
        }

        if (std::abs(mat.at(sel, col)) < EPSILON) {
            continue;
        }

        std::swap(mat.data[sel], mat.data[row]);

        for (int i = row + 1; i < r; ++i) {
            double factor = mat.at(i, col) / mat.at(row, col);
            for (int k = col; k < c; ++k) {
                mat.at(i, k) -= factor * mat.at(row, k);
            }
        }
        ++rankVal;
        ++row;
    }

    return rankVal;
}

// Matrix Inversion using Gauss-Jordan Elimination with Augmented Matrix
Matrix Matrix::inverse() const {
    if (rows != cols) {
        throw std::invalid_argument("Matrix inversion requires a square matrix.");
    }

    int n = rows;
    const double EPSILON = 1e-9;
    
    if (std::abs(determinant()) < EPSILON) {
        throw std::runtime_error("Matrix is singular (determinant is zero) and cannot be inverted.");
    }

    // Create augmented matrix [A | I]
    Matrix aug(n, 2 * n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            aug.at(i, j) = data[i][j];
            aug.at(i, j + n) = (i == j) ? 1.0 : 0.0;
        }
    }

    // Perform Gauss-Jordan elimination
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(aug.at(j, i)) > std::abs(aug.at(pivot, i))) {
                pivot = j;
            }
        }

        if (std::abs(aug.at(pivot, i)) < EPSILON) {
            throw std::runtime_error("Matrix is non-invertible.");
        }

        if (pivot != i) {
            std::swap(aug.data[i], aug.data[pivot]);
        }

        double pivotVal = aug.at(i, i);
        for (int j = 0; j < 2 * n; ++j) {
            aug.at(i, j) /= pivotVal;
        }

        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double factor = aug.at(j, i);
                for (int k = 0; k < 2 * n; ++k) {
                    aug.at(j, k) -= factor * aug.at(i, k);
                }
            }
        }
    }

    // Extract inverse from right half of augmented matrix
    Matrix inv(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inv.at(i, j) = aug.at(i, j + n);
        }
    }

    return inv;
}

} // namespace poly_reg
