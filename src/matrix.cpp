#include "poly_reg/matrix.hpp"
#include <cmath>
#include <algorithm>
#include <iomanip>

namespace PolyReg
{

    // 1. Default Constructor
    // creates an empty matrix of row = 0 and col = 0
    // leaves internal 2D vector empty - grid data
    // used when you need to declare a matrix variable without setting up its sixze immediately
    Matrix::Matrix() : row_dim(0), col_dim(0), grid_data() {}

    // 2. Parameterized Constructor
    // builds a matrix of user defined dimensions
    // fills every cell with a default / initial_val value.
    // takes in row and column dimensions r and c, and a default fill number
    // builds a 2D vector with a starting number.
    Matrix::Matrix(size_t r, size_t c, double initial_val)
        : row_dim(r), col_dim(c), grid_data(r, std::vector<double>(c, initial_val))
    {
        if (r == 0 || c == 0)
        { // error that stops the program when someone tries to create an illegal matrix of r=c=0
            throw std::invalid_argument("Error: Matrix dimensions must be greater than zero.");
        }
    }

    // 3. Initializer List Constructor
    Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init_list) // allows clean brace {} initialization syntax in tests and demos
    {
        row_dim = init_list.size(); // counts how many rows were provided in the outer curly braces.
        if (row_dim == 0)
        { // error if no rows
            throw std::invalid_argument("Error: Initializer list cannot be empty.");
        }
        col_dim = init_list.begin()->size();                     // checks the size of the first row to determine column width
        grid_data.resize(row_dim, std::vector<double>(col_dim)); // resizes internal 2D vector storage to match the dimensions entered
                                                                 // resize tells the computer to make the list of rows have a length of row_dim
                                                                 // and every single row inside it a vector of size col_dim
                                                                 // such that memory is allocated in advance before numbers are copied

        size_t r = 0; // initializes raw tracking index to 0
        // keeps track of which row we are currently fillling as we loop through initializee list
        // always start filling the matrix froom row index 0

        for (const auto &row : init_list)
        { // loops through each row and throws an error if any row has
            // inconsistent width
            if (row.size() != col_dim)
            {
                throw std::invalid_argument("Error: Inconsistent row widths in initializer list.");
            }
            size_t c = 0; // intializes col tracking index to 0
            for (double val : row)
            { // loops through each individual number in the row (calling each val)
                // copies it into the internal grid
                // and advances indices
                grid_data[r][c++] = val;
            }
            r++;
        }
    }

    // Dimension Getters
    // read-only helper functions returning the number of rows and columns
    size_t Matrix::get_rows() const { return row_dim; }
    size_t Matrix::get_cols() const { return col_dim; }

    // Bounds-Checked Element Access (Non-Const)
    double &Matrix::at(size_t r, size_t c)
    { // checks if co-ordinates are out of bounds and throws an error if they are.
        if (r >= row_dim || c >= col_dim)
        {
            throw std::out_of_range("Error: Matrix index out of bounds.");
        }
        return grid_data[r][c];
    }

    // Bounds-Checked Element Access (Const)
    const double &Matrix::at(size_t r, size_t c) const
    { // the same bounds checking but for read only
        if (r >= row_dim || c >= col_dim)
        {
            throw std::out_of_range("Error: Matrix index out of bounds.");
        }
        return grid_data[r][c];
    }

    // Arithmetic Operators
    Matrix Matrix::operator+(const Matrix &other) const
    { // overloads the + operator
        // verifies if both matrices have matching dimensions
        // loops throw every row and col to add corresponding elements
        // returns a new result matrix of the sum
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
    { // overloads the - operator in the same way as the + above
        // but it returns a result matrix of subtracted values.
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
    { // loops through every cell in the matrix and multiplies it by a single number
        // returns a new scaled copy
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
        { // matrix-matrix multiplication
            // validates that inter dimension align i.e no. of r in A == no. of c in B
            // executes dot product algorithm
            // accumulates sums to build the resulting product matrix
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
    { // flips the matrix - turns rxc into cxr
        // i.e turns rows into columns
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
        { // checks if matrix is a square if not, it throws an error because
            // determinants only exist for square matrices
            throw std::runtime_error("Error: Determinant requires a square matrix.");
        }
        size_t n = row_dim; // figures how big the square matrix is
        // if 3x3 then n = 3
        Matrix work = *this; // makes a temporary copy of the matrix
        // thus original matrix is unharmed
        // since calculating the determinant requries modifying numbers
        double det = 1.0; // starts the multiplier for the determinant at 1.0

        // use of Guassian Elimination method to find the determinant.
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
        if (row_dim != col_dim) // ensures that matrix is square
        {
            throw std::runtime_error("Error: Matrix inversion requires a square matrix.");
        }
        size_t n = row_dim;
        if (std::abs(compute_determinant()) < 1e-11) // ensures that det is not 0 since singular matrices can't be inverted
        {
            throw std::runtime_error("Error: Matrix is singular and cannot be inverted.");
        }
        // performs Gauss - Jordan elminations across augmented matrix to find inverse
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
        return inv; // returns inverted matrix
    }

    // Linear System Solver
    Matrix Matrix::solve_linear_system(const Matrix &A, const Matrix &b)
    { // solves equations in the form Ax = b
        Matrix A_inv = A.compute_inverse();
        return A_inv * b;
    }

    // Utility Print
    void Matrix::print() const
    { // prints the matrix values neatly to the console
        for (size_t r = 0; r < row_dim; ++r)
        {
            for (size_t c = 0; c < col_dim; ++c)
            {
                std::cout << std::setw(8) << std::fixed << std::setprecision(4) << grid_data[r][c] << " ";
            }
            std::cout << "\n";
        }
    }

} // namespace PolyReg