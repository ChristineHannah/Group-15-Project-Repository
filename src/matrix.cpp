#include "poly_reg/matrix.hpp"
#include <cmath>
#include <algorithm>
#include <iomanip>

namespace PolyReg
{

    // 1. Default Constructor
    Matrix::Matrix() : row_dim(0), col_dim(0), grid_data() {}

    // 2. Parameterized Constructor
    Matrix::Matrix(size_t r, size_t c, double initial_val)
        : row_dim(r), col_dim(c), grid_data(r, std::vector<double>(c, initial_val))
    {
        if (r == 0 || c == 0)
        {
            throw std::invalid_argument("Error: Matrix dimensions must be greater than zero.");
        }
    }

    // 3. Initializer List Constructor
    Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init_list)
    {
        row_dim = init_list.size();
        if (row_dim == 0)
        {
            throw std::invalid_argument("Error: Initializer list cannot be empty.");
        }
        col_dim = init_list.begin()->size();
        grid_data.resize(row_dim, std::vector<double>(col_dim));

        size_t r = 0;
        for (const auto &row : init_list)
        {
            if (row.size() != col_dim)
            {
                throw std::invalid_argument("Error: Inconsistent row widths in initializer list.");
            }
            size_t c = 0;
            for (double val : row)
            {
                grid_data[r][c++] = val;
            }
            r++;
        }
    }

    // Dimension Getters
    size_t Matrix::get_rows() const { return row_dim; }
    size_t Matrix::get_cols() const { return col_dim; }

    // Bounds-Checked Element Access (Non-Const)
    double &Matrix::at(size_t r, size_t c)
    {
        if (r >= row_dim || c >= col_dim)
        {
            throw std::out_of_range("Error: Matrix index out of bounds.");
        }
        return grid_data[r][c];
    }

    // Bounds-Checked Element Access (Const)
    const double &Matrix::at(size_t r, size_t c) const
    {
        if (r >= row_dim || c >= col_dim)
        {
            throw std::out_of_range("Error: Matrix index out of bounds.");
        }
        return grid_data[r][c];
    }

    // Arithmetic Operators
    Matrix Matrix::operator+(const Matrix &other) const
    {
        if (row_dim != other.row_dim || col_dim != other.col_dim)
        {
            throw std::invalid_argument("Error: Dimension mismatch for addition.");
        }
        Matrix result(row_dim, col_dim);
        for (size_t r = 0; r < row_dim; ++r)
        {
            for (size_t c = 0; c < col_dim; ++c)
            {
                result.grid_data[r][c] = grid_data[r][c] + other.grid_data[r][c];
            }
        }
        return result;
    }

    Matrix Matrix::operator-(const Matrix &other) const
    {
        if (row_dim != other.row_dim || col_dim != other.col_dim)
        {
            throw std::invalid_argument("Error: Dimension mismatch for subtraction.");
        }
        Matrix result(row_dim, col_dim);
        for (size_t r = 0; r < row_dim; ++r)
        {
            for (size_t c = 0; c < col_dim; ++c)
            {
                result.grid_data[r][c] = grid_data[r][c] - other.grid_data[r][c];
            }
        }
        return result;
    }

    Matrix Matrix::operator*(double scalar) const
    {
        Matrix result(row_dim, col_dim);
        for (size_t r = 0; r < row_dim; ++r)
        {
            for (size_t c = 0; c < col_dim; ++c)
            {
                result.grid_data[r][c] = grid_data[r][c] * scalar;
            }
        }
        return result;
    }

    Matrix Matrix::operator*(const Matrix &other) const
    {
        if (col_dim != other.row_dim)
        {
            throw std::invalid_argument("Error: Inner dimensions do not match for multiplication.");
        }
        Matrix result(row_dim, other.col_dim, 0.0);
        for (size_t r = 0; r < row_dim; ++r)
        {
            for (size_t c = 0; c < other.col_dim; ++c)
            {
                double sum = 0.0;
                for (size_t k = 0; k < col_dim; ++k)
                {
                    sum += grid_data[r][k] * other.grid_data[k][c];
                }
                result.grid_data[r][c] = sum;
            }
        }
        return result;
    }

    // Matrix Transposition
    Matrix Matrix::transpose() const
    {
        Matrix result(col_dim, row_dim);
        for (size_t r = 0; r < row_dim; ++r)
        {
            for (size_t c = 0; c < col_dim; ++c)
            {
                result.grid_data[c][r] = grid_data[r][c];
            }
        }
        return result;
    }

    // Advanced Linear Algebra: Determinant
    double Matrix::compute_determinant() const
    {
        if (row_dim != col_dim)
        {
            throw std::runtime_error("Error: Determinant requires a square matrix.");
        }
        size_t n = row_dim;
        Matrix work = *this;
        double det = 1.0;

        for (size_t i = 0; i < n; ++i)
        {
            size_t pivot = i;
            while (pivot < n && std::abs(work.at(pivot, i)) < 1e-11)
            {
                pivot++;
            }
            if (pivot == n)
                return 0.0;
            if (pivot != i)
            {
                std::swap(work.grid_data[i], work.grid_data[pivot]);
                det *= -1.0;
            }
            det *= work.at(i, i);
            for (size_t j = i + 1; j < n; ++j)
            {
                double factor = work.at(j, i) / work.at(i, i);
                for (size_t k = i; k < n; ++k)
                {
                    work.at(j, k) -= factor * work.at(i, k);
                }
            }
        }
        return det;
    }

    // Advanced Linear Algebra: Inverse
    Matrix Matrix::compute_inverse() const
    {
        if (row_dim != col_dim)
        {
            throw std::runtime_error("Error: Matrix inversion requires a square matrix.");
        }
        size_t n = row_dim;
        if (std::abs(compute_determinant()) < 1e-11)
        {
            throw std::runtime_error("Error: Matrix is singular and cannot be inverted.");
        }

        Matrix aug(n, 2 * n, 0.0);
        for (size_t r = 0; r < n; ++r)
        {
            for (size_t c = 0; c < n; ++c)
            {
                aug.at(r, c) = grid_data[r][c];
            }
            aug.at(r, r + n) = 1.0;
        }

        for (size_t i = 0; i < n; ++i)
        {
            size_t pivot = i;
            while (pivot < n && std::abs(aug.at(pivot, i)) < 1e-11)
            {
                pivot++;
            }
            if (pivot != i)
            {
                std::swap(aug.grid_data[i], aug.grid_data[pivot]);
            }
            double pivot_val = aug.at(i, i);
            for (size_t c = 0; c < 2 * n; ++c)
            {
                aug.at(i, c) /= pivot_val;
            }
            for (size_t r = 0; r < n; ++r)
            {
                if (r != i)
                {
                    double factor = aug.at(r, i);
                    for (size_t c = 0; c < 2 * n; ++c)
                    {
                        aug.at(r, c) -= factor * aug.at(i, c);
                    }
                }
            }
        }

        Matrix inv(n, n);
        for (size_t r = 0; r < n; ++r)
        {
            for (size_t c = 0; c < n; ++c)
            {
                inv.at(r, c) = aug.at(r, c + n);
            }
        }
        return inv;
    }

    // Linear System Solver
    Matrix Matrix::solve_linear_system(const Matrix &A, const Matrix &b)
    {
        Matrix A_inv = A.compute_inverse();
        return A_inv * b;
    }

    // Utility Print
    void Matrix::print() const
    {
        for (size_t r = 0; r < row_dim; ++r)
        {
            for (size_t c = 0; c < col_dim; ++c)
            {
                std::cout << std::setw(8) << std::fixed << std::setprecision(4) << grid_data[r][c] << " ";
            }
            std::cout << "\n";
        }
    }

} // namespace PolyRegC