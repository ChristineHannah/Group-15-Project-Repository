#ifndef POLY_REG_MATRIX_HPP
#define POLY_REG_MATRIX_HPP

#include <vector>
#include <stdexcept>

namespace poly_reg {

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<double>> data;

public:
    // Constructors & Basic Getters
    Matrix(int r, int c);
    Matrix(const std::vector<std::vector<double>>& values);

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    
    double& at(int r, int c);
    double at(int r, int c) const;

    // Advanced Matrix Operations for Normal Equations
    double determinant() const;
    int rank() const;
    Matrix inverse() const;

    // Helper Utility
    static Matrix identity(int n);
};

} // namespace poly_reg

#endif // POLY_REG_MATRIX_HPP
