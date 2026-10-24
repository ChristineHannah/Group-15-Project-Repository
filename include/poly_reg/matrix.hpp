#pragma once
#include <vector>
#include <stdexcept>
#include <initializer_list>
#include <cmath>
#include <iostream>

namespace PolyReg
{
    class Matrix
    {
    private:
        size_t row_dim;
        size_t col_dim;
        std::vector<std::vector<double>> grid_data;

    public:
        // 1. Default Constructor (Fixes weight_coefficients() error)
        Matrix();

        // 2. Dimension & Initial Value Constructor
        Matrix(size_t r, size_t c, double initial_val = 0.0);

        // 3. Initializer List Constructor (Fixes test initialization ambiguity)
        Matrix(std::initializer_list<std::initializer_list<double>> init_list);

        ~Matrix() = default;

        // Dimension Getters
        size_t get_rows() const;
        size_t get_cols() const;

        // Compatibility aliases
        size_t rows() const { return row_dim; }
        size_t cols() const { return col_dim; }

        // Safe Element Access with Bounds Checking
        double &at(size_t r, size_t c);
        const double &at(size_t r, size_t c) const;

        // Core Arithmetic Operators
        Matrix operator+(const Matrix &other) const;
        Matrix operator-(const Matrix &other) const;
        Matrix operator*(double scalar) const;
        Matrix operator*(const Matrix &other) const;

        // Helper Method for Gradient Descent (Fixes scalar_multiply error)
        Matrix scalar_multiply(double scalar) const
        {
            return (*this) * scalar;
        }

        // Member Function Aliases for Test Suites
        Matrix add(const Matrix &other) const { return (*this) + other; }
        Matrix subtract(const Matrix &other) const { return (*this) - other; }
        Matrix multiply(const Matrix &other) const { return (*this) * other; }

        // Matrix Transformations & Advanced Solvers
        Matrix transpose() const;
        double compute_determinant() const;
        Matrix compute_inverse() const;
        static Matrix solve_linear_system(const Matrix &coefficient_matrix, const Matrix &constant_vector);

        // Utility Print
        void print() const;
    };
} // namespace PolyReg