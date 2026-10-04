#include "matrix.hpp"

#include <stdexcept>
namespace poly_reg {
    Matrix::Matrix() : rows_(0), cols_(0), data_() {} //empty matrix
    Matrix::Matrix(std::size_t rows, std::size_t cols) : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}//matrix of a given size, creates a list with all items set to 0.0
    Matrix::Matrix(std::initializer_list<std::initializer_list<double>> values)
        : rows_(values.size()), cols_(0), data_() {
        if (rows_ > 0) {
            cols_ = values.begin()->size();
        }

        // reserve space to prevent unnecessary repeated vector growth
        data_.reserve(rows_ * cols_);

        for (const auto& row : values) {
            if (row.size() != cols_) {
                throw std::invalid_argument("All rows must have the same number of columns");
            }
            for (double value : row) {
                data_.push_back(value);
            }
        }
    }

    // size getters
    std::size_t Matrix::rows() const { return rows_; }
    std::size_t Matrix::cols() const { return cols_; }

    // element access
    // read + write version
    double& Matrix::operator()(std::size_t r, std::size_t c) {
        // index should be inside the grid
        if (r >= rows_ || c >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[r * cols_ + c];
    }

    // read only version (used when matrix is const)
    const double& Matrix::operator()(std::size_t r, std::size_t c) const {
        if (r >= rows_ || c >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[r * cols_ + c];
    }

    // math operations

    // Addition of matrices
    Matrix Matrix::operator+(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition");
        }

        Matrix result(rows_, cols_);  // New matrix to hold answer
        for (std::size_t i = 0; i < data_.size(); ++i) {
            result.data_[i] = data_[i] + other.data_[i];
        }
        return result;
    }

    // Subtraction of matrices
    Matrix Matrix::operator-(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
        }

        Matrix result(rows_, cols_);
        for (std::size_t i = 0; i < data_.size(); ++i) {
            result.data_[i] = data_[i] - other.data_[i];
        }
        return result;
    }

    // Scalar Multiplication
    Matrix Matrix::operator*(double scalar) const {
        Matrix result(rows_, cols_);
        for (std::size_t i = 0; i < data_.size(); ++i) {
            result.data_[i] = data_[i] * scalar;
        }
        return result;
    }

    // Matrix by Matrix Multiplication
    Matrix Matrix::operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Left columns must equal right rows");
        }

        Matrix result(rows_, other.cols_);
        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < other.cols_; ++j) {
                double sum = 0.0;
                for (std::size_t k = 0; k < cols_; ++k) {
                    sum += data_[i * cols_ + k] * other.data_[k * other.cols_ + j];
                }
                result.data_[i * result.cols_ + j] = sum;
            }
        }
        return result;
    }

    // Transpose of a matrix
    Matrix Matrix::transpose() const {
        Matrix result(cols_, rows_);
        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < cols_; ++j) {
                result.data_[j * result.cols_ + i] = data_[i * cols_ + j];
            }
        }
        return result;
    }
}  // namespace poly_reg
