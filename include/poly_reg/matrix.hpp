// matrix.h
#pragma once // Ensures this file is included only once per build.

#include <cstddef> // std::size_t is used for size types.
#include <initializer_list> // std::initializer_list is used for constructors taking a list of lists.
#include <vector> // std::vector is used to store the matrix data.

namespace poly_reg {
    class Matrix {
    public:
        //constructors
        Matrix(); //empty matrix
        Matrix(std::size_t rows, std::size_t cols); //matrix of a given size, creates a list with all items set to 0.0
        Matrix(std::initializer_list<std::initializer_list<double>> values); //matrix from a list of lists

        //size getters
        std::size_t rows() const;
        std::size_t cols() const;

        //element access
        double& operator()(std::size_t r, std::size_t c); //read + write version.
        const double& operator()(std::size_t r, std::size_t c) const; //read only version(used when matrix is const)

        //math operations
        Matrix operator+(const Matrix& other) const; //Addition of matrices

        Matrix operator-(const Matrix& other) const; //Subtraction of matrices

        Matrix operator*(double scalar) const; //Scalar multiplication

        Matrix operator*(const Matrix& other) const; //Matrix multiplication

        Matrix transpose() const; //Transpose of a matrix

    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<double> data_; //1D vector to store matrix data in row-major order
    };
}