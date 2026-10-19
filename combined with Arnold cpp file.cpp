#include "combined with Arnold hpp file.cpp"
#include <cmath>
#include <algorithm>

namespace PolyReg {

Matrix::Matrix() : row_dimension(0), column_dimension(0) {}

Matrix::Matrix(int rows, int cols, double initial_value)
    : row_dimension(rows), column_dimension(cols),
      grid_element_storage(rows, std::vector<double>(cols, initial_value)) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Error: Matrix dimensions must be greater than zero.");
    }
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> initial_values) {
    row_dimension = initial_values.size();
    if (row_dimension == 0) {
        throw std::invalid_argument("Error: Initializer list cannot be empty.");
    }
    column_dimension = initial_values.begin()->size();

    grid_element_storage.resize(row_dimension, std::vector<double>(column_dimension));

    int row_idx = 0;
    for (const auto& row_elements : initial_values) {
        if (static_cast<int>(row_elements.size()) != column_dimension) {
            throw std::invalid_argument("Error: Inconsistent row widths in matrix initializer list.");
        }
        int col_idx = 0;
        for (double val : row_elements) {
            grid_element_storage[row_idx][col_idx++] = val;
        }
        row_idx++;
    }
}

int Matrix::get_rows() const { return row_dimension; }
int Matrix::get_cols() const { return column_dimension; }

double& Matrix::at(int row_index, int col_index) {
    if (row_index < 0 || row_index >= row_dimension || col_index < 0 || col_index >= column_dimension) {
        throw std::out_of_range("Error: Matrix index out of bounds.");
    }
    return grid_element_storage[row_index][col_index];
}

const double& Matrix::at(int row_index, int col_index) const {
    if (row_index < 0 || row_index >= row_dimension || col_index < 0 || col_index >= column_dimension) {
        throw std::out_of_range("Error: Matrix index out of bounds.");
    }
    return grid_element_storage[row_index][col_index];
}

Matrix Matrix::add(const Matrix& other_matrix) const {
    if (row_dimension != other_matrix.row_dimension || column_dimension != other_matrix.column_dimension) {
        throw std::invalid_argument("Error: Matrix dimensions must match for addition.");
    }

    Matrix sum_result(row_dimension, column_dimension);
    for (int r = 0; r < row_dimension; ++r) {
        for (int c = 0; c < column_dimension; ++c) {
            sum_result.grid_element_storage[r][c] = grid_element_storage[r][c] + other_matrix.grid_element_storage[r][c];
        }
    }
    return sum_result;
}

Matrix Matrix::multiply(const Matrix& other_matrix) const {
    if (column_dimension != other_matrix.row_dimension) {
        throw std::invalid_argument("Error: Inner matrix dimensions must match for multiplication.");
    }

    Matrix product_result(row_dimension, other_matrix.column_dimension, 0.0);
    for (int r = 0; r < row_dimension; ++r) {
        for (int c = 0; c < other_matrix.column_dimension; ++c) {
            double accumulated_sum = 0.0;
            for (int k = 0; k < column_dimension; ++k) {
                accumulated_sum += grid_element_storage[r][k] * other_matrix.grid_element_storage[k][c];
            }
            product_result.grid_element_storage[r][c] = accumulated_sum;
        }
    }
    return product_result;
}

Matrix Matrix::transpose() const {
    Matrix transposed_result(column_dimension, row_dimension);
    for (int r = 0; r < row_dimension; ++r) {
        for (int c = 0; c < column_dimension; ++c) {
            transposed_result.grid_element_storage[c][r] = grid_element_storage[r][c];
        }
    }
    return transposed_result;
}

double Matrix::compute_determinant() const {
    if (row_dimension != column_dimension) {
        throw std::runtime_error("Error: Determinant requires a square matrix.");
    }

    int n = row_dimension;
    Matrix working_matrix = *this;
    double determinant_value = 1.0;

    for (int i = 0; i < n; ++i) {
        int pivot_row = i;
        while (pivot_row < n && std::abs(working_matrix.at(pivot_row, i)) < 1e-11) {
            pivot_row++;
        }

        if (pivot_row == n) {
            return 0.0; // Singular matrix
        }

        if (pivot_row != i) {
            std::swap(working_matrix.grid_element_storage[i], working_matrix.grid_element_storage[pivot_row]);
            determinant_value *= -1.0;
        }

        determinant_value *= working_matrix.at(i, i);

        for (int j = i + 1; j < n; ++j) {
            double factor = working_matrix.at(j, i) / working_matrix.at(i, i);
            for (int k = i; k < n; ++k) {
                working_matrix.at(j, k) -= factor * working_matrix.at(i, k);
            }
        }
    }

    return determinant_value;
}

Matrix Matrix::compute_inverse() const {
    if (row_dimension != column_dimension) {
        throw std::runtime_error("Error: Matrix inversion requires a square matrix.");
    }

    int n = row_dimension;
    double det = compute_determinant();
    if (std::abs(det) < 1e-11) {
        throw std::runtime_error("Error: Matrix is singular and cannot be inverted.");
    }

    // Construct augmented matrix [A | I]
    Matrix augmented(n, 2 * n, 0.0);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            augmented.at(r, c) = grid_element_storage[r][c];
        }
        augmented.at(r, r + n) = 1.0;
    }

    // Gauss-Jordan elimination
    for (int i = 0; i < n; ++i) {
        int pivot_row = i;
        while (pivot_row < n && std::abs(augmented.at(pivot_row, i)) < 1e-11) {
            pivot_row++;
        }

        if (pivot_row != i) {
            std::swap(augmented.grid_element_storage[i], augmented.grid_element_storage[pivot_row]);
        }

        double pivot_element = augmented.at(i, i);
        for (int c = 0; c < 2 * n; ++c) {
            augmented.at(i, c) /= pivot_element;
        }

        for (int r = 0; r < n; ++r) {
            if (r != i) {
                double scaling_factor = augmented.at(r, i);
                for (int c = 0; c < 2 * n; ++c) {
                    augmented.at(r, c) -= scaling_factor * augmented.at(i, c);
                }
            }
        }
    }

    // Extract inverse matrix from the right half of the augmented matrix
    Matrix inverse_result(n, n);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            inverse_result.at(r, c) = augmented.at(r, c + n);
        }
    }

    return inverse_result;
}

} // namespace PolyReg