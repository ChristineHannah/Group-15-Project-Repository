#include "poly_reg/matrix.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace poly_reg {
namespace {
    void require_square(const Matrix& matrix) {
        if (matrix.rows() != matrix.cols()) {
            throw std::invalid_argument("Matrix must be square");
        }
    }

    double pivot_tolerance(const Matrix& matrix) {
        double scale = 0.0;
        for (std::size_t row = 0; row < matrix.rows(); ++row) {
            for (std::size_t col = 0; col < matrix.cols(); ++col) {
                scale = std::max(scale, std::abs(matrix(row, col)));
            }
        }
        return std::numeric_limits<double>::epsilon() * scale * matrix.rows();
    }

    std::size_t pivot_row(const Matrix& matrix, std::size_t col, std::size_t first_row) {
        std::size_t best_row = first_row;
        for (std::size_t row = first_row + 1; row < matrix.rows(); ++row) {
            if (std::abs(matrix(row, col)) > std::abs(matrix(best_row, col))) {
                best_row = row;
            }
        }
        return best_row;
    }

    void swap_rows(Matrix& matrix, std::size_t first, std::size_t second) {
        for (std::size_t col = 0; col < matrix.cols(); ++col) {
            std::swap(matrix(first, col), matrix(second, col));
        }
    }
}

double Matrix::determinant() const {
    require_square(*this);

    Matrix upper = *this;
    const double tolerance = pivot_tolerance(upper);
    double result = 1.0;

    for (std::size_t col = 0; col < rows_; ++col) {
        const std::size_t best_row = pivot_row(upper, col, col);
        const double pivot = upper(best_row, col);
        if (std::abs(pivot) <= tolerance) {
            return 0.0;
        }
        if (best_row != col) {
            swap_rows(upper, col, best_row);
            result = -result;
        }
        result *= upper(col, col);

        for (std::size_t row = col + 1; row < rows_; ++row) {
            const double factor = upper(row, col) / upper(col, col);
            for (std::size_t next_col = col + 1; next_col < cols_; ++next_col) {
                upper(row, next_col) -= factor * upper(col, next_col);
            }
            upper(row, col) = 0.0;
        }
    }
    return result;
}

Matrix Matrix::inverse() const {
    require_square(*this);

    Matrix left = *this;
    Matrix right(rows_, cols_);
    for (std::size_t i = 0; i < rows_; ++i) {
        right(i, i) = 1.0;
    }

    const double tolerance = pivot_tolerance(left);
    for (std::size_t col = 0; col < rows_; ++col) {
        const std::size_t best_row = pivot_row(left, col, col);
        if (std::abs(left(best_row, col)) <= tolerance) {
            throw std::domain_error("Matrix is singular and cannot be inverted");
        }
        if (best_row != col) {
            swap_rows(left, col, best_row);
            swap_rows(right, col, best_row);
        }

        const double pivot = left(col, col);
        for (std::size_t j = 0; j < cols_; ++j) {
            left(col, j) /= pivot;
            right(col, j) /= pivot;
        }

        for (std::size_t row = 0; row < rows_; ++row) {
            if (row == col) {
                continue;
            }
            const double factor = left(row, col);
            for (std::size_t j = 0; j < cols_; ++j) {
                left(row, j) -= factor * left(col, j);
                right(row, j) -= factor * right(col, j);
            }
        }
    }
    return right;
}

Matrix Matrix::solve(const Matrix& right_hand_side) const {
    require_square(*this);
    if (right_hand_side.rows() != rows_) {
        throw std::invalid_argument("Right-hand side row count must match the coefficient matrix");
    }

    Matrix coefficients = *this;
    Matrix result = right_hand_side;
    const double tolerance = pivot_tolerance(coefficients);

    for (std::size_t col = 0; col < rows_; ++col) {
        const std::size_t best_row = pivot_row(coefficients, col, col);
        if (std::abs(coefficients(best_row, col)) <= tolerance) {
            throw std::domain_error("Linear system has no unique solution");
        }
        if (best_row != col) {
            swap_rows(coefficients, col, best_row);
            swap_rows(result, col, best_row);
        }

        for (std::size_t row = col + 1; row < rows_; ++row) {
            const double factor = coefficients(row, col) / coefficients(col, col);
            coefficients(row, col) = 0.0;
            for (std::size_t j = col + 1; j < cols_; ++j) {
                coefficients(row, j) -= factor * coefficients(col, j);
            }
            for (std::size_t j = 0; j < result.cols(); ++j) {
                result(row, j) -= factor * result(col, j);
            }
        }
    }

    for (std::size_t row = rows_; row-- > 0;) {
        for (std::size_t col = 0; col < result.cols(); ++col) {
            for (std::size_t next_col = row + 1; next_col < cols_; ++next_col) {
                result(row, col) -= coefficients(row, next_col) * result(next_col, col);
            }
            result(row, col) /= coefficients(row, row);
        }
    }
    return result;
}
}  // namespace poly_reg