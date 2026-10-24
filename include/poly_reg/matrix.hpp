#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>

namespace PolyReg
{

    class Matrix
    {
    private:
        size_t rows;
        size_t cols;
        std::vector<std::vector<double>> data;

    public:
        // Constructors & Destructor
        Matrix(size_t r, size_t c, double initial_val = 0.0);
        Matrix(const std::vector<std::vector<double>> &input_data);
        ~Matrix() = default;

        // Dimension Accessors
        size_t get_rows() const;
        size_t get_cols() const;

        // Element Access (Bounds-Checked)
        double &at(size_t r, size_t c);
        const double &at(size_t r, size_t c) const;

        // Core Arithmetic Operators (Arnold's Work)
        Matrix add(const Matrix &other) const;
        Matrix subtract(const Matrix &other) const;
        Matrix multiply(double scalar) const;
        Matrix multiply(const Matrix &other) const;

        // Matrix Transformation (Arnold's Work)
        Matrix transpose() const;

        // --- Advanced Linear Algebra Extensions (Added by Joshua) ---

        /**
         * Computes the determinant of a square matrix using Gaussian elimination or cofactor expansion.
         */
        double compute_determinant() const;

        /**
         * Computes the inverse of a square matrix using Gauss-Jordan elimination.
         */
        Matrix compute_inverse() const;

        /**
         * Solves a linear system of equations of the form Ax = b.
         */
        static Matrix solve_linear_system(const Matrix &A, const Matrix &b);

        // Utility
        void print() const;
    };

} // namespace PolyReg