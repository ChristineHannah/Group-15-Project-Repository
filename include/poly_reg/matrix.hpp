#pragma once // preprocessor directive that ensures the header file is included only once in a single compilation, preventing duplicate definitions and potential conflicts. A must include at the top of every header file.
// It say to the complier : Read this header file ONLY ONCE per compilation no matter how many files ask for it.
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
        // private the ensure that rows and cols always mathematically match the actual size of the vector
        // if it were not private and someone changeed rows to 100 without resizing the underlying vector, the program would crash out or corrupt memory during loops.
        // since private, it forces safe bounds checked access to rows and cols through public member functions that throw out_of_range exceptions if the user tries to access an invalid index. This prevents memory corruption and crashes.
    public: // provide safe ways for users to interact with the machine without risking damage.
        // 1. Default Constructor (Fixes weight_coefficients() error)
        Matrix();

        // 2. Dimension & Initial Value Constructor
        Matrix(size_t r, size_t c, double initial_val = 0.0); // It initializes a grid of dimensions r X c filled with  a default value.

        // 3. Initializer List Constructor (Fixes test initialization ambiguity)
        Matrix(std::initializer_list<std::initializer_list<double>> init_list); // Allows brace initialization syntax such as Matrx A = {{1,2}, {3,5}}. It helps to create a matrix with specific values in a more readable way.

        ~Matrix() = default; // A destructor that is defaulted, meaning it will automatically clean up the resources used by the Matrix object when it goes out of scope.

        // Dimension Getters
        // Returns the number of rows and columns in the matrix.
        // Because the actual rows and cols variables are private, external code uses a const member functions to safely ask "How many rows does the matrix have?"
        size_t get_rows() const;
        size_t get_cols() const; // size_t is data type representing a positive integer used for sizes and counts.

        // Compatibility aliases - same as the ones just before.
        // Because different team members may have different preferences for how to express matrix dimensions, these aliases provide flexibility in how the code can be written and read.
        size_t rows() const { return row_dim; }
        size_t cols() const { return col_dim; }

        // Safe Element Access with Bounds Checking. Provides bounds-checked safe element access.
        double &at(size_t r, size_t c);             // returns a modifiable reference to the number sitting at r or c. It can be used to either read or change a value. It first checks if r and c are valid - if not it throws an out_of_range exception instead of crashing the computer.
        const double &at(size_t r, size_t c) const; // does the same bound checking but returns only a read only reference meaning you cannot modify the value.

        // Core Arithmetic Operators
        // Operator overloaders for matrix addition, subtraction, scalar multiplication and matix-matrix multiplication. These allow you to use the standard arithmetic symbols (+, -, *) with Matrix objects in a natural way.
        Matrix operator+(const Matrix &other) const;
        Matrix operator-(const Matrix &other) const;
        Matrix operator*(double scalar) const;       // such as A* 6.0
        Matrix operator*(const Matrix &other) const; // such as A * B. This function should validate that inner dimensions align eg cols of A == rows of B. If not, it should throw an exception.

        // Helper Method for Gradient Descent (Fixes scalar_multiply error)
        // It multiplies every single number inside the matrix by the scalar value.
        // Loops through each value at grid[r][c] and multiplies b the scalar and stores it in a brand new resulting matrix
        // const shows that the original matrix obkected is untouched and instead a new scaled matrix copy is obtained.
        Matrix scalar_multiply(double scalar) const
        {
            return (*this) * scalar;
        }

        // Member Function Aliases for Test Suites
        // Same as the operator overloads above but with more descriptive names.
        // This is because different team members may have different preferences for how to express matrix operations, so these aliases provide flexibility in how the code can be written and read.
        // They ensure that both syntaxes work seamlessly without breaking compilation.
        Matrix add(const Matrix &other) const { return (*this) + other; }
        Matrix subtract(const Matrix &other) const { return (*this) - other; }
        Matrix multiply(const Matrix &other) const { return (*this) * other; }

        // Matrix Transformations & Advanced Solvers
        Matrix transpose() const;           // this function returns a new matrix that is the transpose of the current matrix, i.e the rows become columns and the columns become rows for the new matrix. It is useful in linear algebra operations.
        double compute_determinant() const; // this function calculates the determinant of a square matrix.
        Matrix compute_inverse() const;     // computes the inverse of a square matrix using Gaussian elimination. If the matrix is singular (non-invertible), it throws an exception.
        //
        static Matrix solve_linear_system(const Matrix &coefficient_matrix, const Matrix &constant_vector); // a heavy duty math solver for equations with multiple unknowns.
                                                                                                            // solves linear equations of the form Ax = b where A is the coefficient matrix, b is the constant vector and x is the unknown vector.
        // It is a secret sause of the Ordinary Lease Squares (OLS) regression. Used in the forumla for finding best-fit curve weights Beta in the normal equation: Beta = (X^T * X)^-1 * X^T * y.

        // Utility Print
        void print() const; // this loops through 2D grid rows and colummns using the nested for loops and prints the matrix values to the terminal.
        // Useful for debugging and inspecting matrix values during demos.
    };
} // namespace PolyReg

// Namespace PolyReg is like a folder that wraps all the project's classes such that if another library in C++ also has a class named Matrix, the computer won't get confused because ours is safely inside PolyReg::Matrix.