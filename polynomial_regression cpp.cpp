// src/polynomial_regression.cpp (Arnold's Base Implementation)
#include "poly_reg/polynomial_regression.hpp"
#include "poly_reg/feature_expansion.hpp"
#include <stdexcept>

namespace PolyReg {
    PolynomialRegression::PolynomialRegression(int poly_degree) : degree(poly_degree) {}

    // Computes X^T * X
    Matrix PolynomialRegression::compute_transpose_product(const Matrix& X) const {
        Matrix X_transpose = X.transpose();
        return X_transpose.multiply(X);
    }

    // Computes X^T * y
    Matrix PolynomialRegression::compute_normal_equation_rhs(const Matrix& X, const Matrix& y) const {
        Matrix X_transpose = X.transpose();
        return X_transpose.multiply(y);
    }

    Matrix PolynomialRegression::predict(const Matrix& X_input) const {
        Matrix design_matrix = FeatureExpansion::create_polynomial_features(X_input, degree);
        return design_matrix.multiply(coefficients);
    }
}