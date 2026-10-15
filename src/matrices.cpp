#include "poly_reg/matrix.hpp"

#include <stdexcept>

using namespace std;

namespace poly_reg {

Matrix::Matrix() : rows_(0), cols_(0), data_() {}

Matrix::Matrix(size_t rows, size_t cols)
    : rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}

Matrix::Matrix(initializer_list<initializer_list<double>> values)
    : rows_(values.size()), cols_(0), data_()
{
    if (rows_ > 0) {
        cols_ = values.begin()->size();
    }

    data_.reserve(rows_ * cols_);
    for (const auto& row : values) {
        if (row.size() != cols_) {
            throw invalid_argument("All rows must have the same number of columns");
        }
        for (double value : row) {
            data_.push_back(value);
        }
    }
}

size_t Matrix::rows() const { return rows_; }
size_t Matrix::cols() const { return cols_; }

double& Matrix::operator()(size_t row, size_t column)
{
    if (row >= rows_ || column >= cols_) {
        throw out_of_range("Matrix index out of range");
    }
    return data_[row * cols_ + column];
}

const double& Matrix::operator()(size_t row, size_t column) const
{
    if (row >= rows_ || column >= cols_) {
        throw out_of_range("Matrix index out of range");
    }
    return data_[row * cols_ + column];
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw invalid_argument("Matrices must have the same dimensions for addition");
    }

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const
{
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw invalid_argument("Matrices must have the same dimensions for subtraction");
    }

    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] - other.data_[i];
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const
{
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < data_.size(); ++i) {
        result.data_[i] = data_[i] * scalar;
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    if (cols_ != other.rows_) {
        throw invalid_argument("Left columns must equal right rows");
    }

    Matrix result(rows_, other.cols_);
    for (size_t row = 0; row < rows_; ++row) {
        for (size_t column = 0; column < other.cols_; ++column) {
            double sum = 0.0;
            for (size_t k = 0; k < cols_; ++k) {
                sum += data_[row * cols_ + k] * other.data_[k * other.cols_ + column];
            }
            result.data_[row * result.cols_ + column] = sum;
        }
    }
    return result;
}

Matrix Matrix::transpose() const
{
    Matrix result(cols_, rows_);
    for (size_t row = 0; row < rows_; ++row) {
        for (size_t column = 0; column < cols_; ++column) {
            result.data_[column * result.cols_ + row] = data_[row * cols_ + column];
        }
    }
    return result;
}

} // namespace poly_reg
