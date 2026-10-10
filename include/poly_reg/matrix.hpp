#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <stdexcept>

namespace poly_reg {

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

public:
    // 1. Default Constructor
    Matrix() : rows(0), cols(0) {}

    // 2. Parameterized Constructor (dimensions with zero initialization)
    Matrix(int r, int c) : rows(r), cols(c), data(r, std::vector<double>(c, 0.0)) {
        if (r <= 0 || c <= 0) {
            throw std::runtime_error("Error: Matrix dimensions must be greater than zero.");
        }
    }

    // 3. Parameterized Constructor with initial fill value
    Matrix(int r, int c, double initial_value) : rows(r), cols(c), data(r, std::vector<double>(c, initial_value)) {
        if (r <= 0 || c <= 0) {
            throw std::runtime_error("Error: Matrix dimensions must be greater than zero.");
        }
    }

    // Dimension Getters
    int get_rows() const { return rows; }
    int get_cols() const { return cols; }

    // 4. Element Indexing with bounds checking
    double& at(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw std::out_of_range("Error: Matrix index out of bounds.");
        }
        return data[r][c];
    }

    const double& at(int r, int c) const {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw std::out_of_range("Error: Matrix index out of bounds.");
        }
        return data[r][c];
    }

    // 5. Matrix Addition
    Matrix add(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Error: Matrix dimensions must match for addition.");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // 6. Scalar Multiplication
    Matrix multiply_scalar(double scalar) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    // 7. Matrix-Matrix Multiplication
    Matrix multiply(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::runtime_error("Error: Columns of first matrix must match rows of second matrix for multiplication.");
        }
        Matrix result(rows, other.cols, 0.0);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                double sum = 0.0;
                for (int k = 0; k < cols; ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
        return result;
    }

    // 8. Matrix Transpose (Flipping rows into columns)
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }
};

} // namespace poly_reg

#endif // MATRIX_HPP
