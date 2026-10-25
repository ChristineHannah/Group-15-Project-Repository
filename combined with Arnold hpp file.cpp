#pragma once

#include <vector>
#include <stdexcept>
#include <initializer_list>

namespace PolyReg {

class Matrix {
private:
    int row_dimension;
    int column_dimension;
    std::vector<std::vector<double>> grid_element_storage;

public:
    // Constructors
    Matrix();
    Matrix(int rows, int cols, double initial_value = 0.0);
    Matrix(std::initializer_list<std::initializer_list<double>> initial_values);

    // Dimension getters
    int get_rows() const;
    int get_cols() const;

    // Safe element access with bounds checking
    double& at(int row_index, int col_index);
    const double& at(int row_index, int col_index) const;

    // Arnold's Core Infrastructure Operations
    Matrix add(const Matrix& other_matrix) const;
    Matrix multiply(const Matrix& other_matrix) const;
    Matrix transpose() const;

    // Joshua's Advanced Linear Algebra Solvers
    double compute_determinant() const;
    Matrix compute_inverse() const;
};

} // namespace PolyReg