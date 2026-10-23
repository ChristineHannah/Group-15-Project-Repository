// src/polynomial_regression.cpp (Arnold & Joshua Merged Implementation)
#include "poly_reg/polynomial_regression.hpp"
#include "poly_reg/feature_expansion.hpp"
#include <cmath>
#include <stdexcept>

namespace PolyReg {
    PolynomialRegression::PolynomialRegression(int poly_degree) : degree(poly_degree) {}

    // Complete OLS Fitting: beta = (X^T * X)^-1 * X^T * y
    void PolynomialRegression::fit(const Matrix& X_input, const Matrix& y_target) {
        if (X_input.get_rows() != y_target.get_rows()) {
            throw std::invalid_argument("Error: Row mismatch between input features and target vector.");
        }

        // Step 1: Expand features into polynomial design matrix X
        Matrix X = FeatureExpansion::create_polynomial_features(X_input, degree);

        // Step 2: Compute X transpose
        Matrix X_t = X.transpose();

        // Step 3: Compute X^T * X (Arnold's work)
        Matrix XtX = X_t.multiply(X);

        // Step 4: Compute X^T * y (Arnold's work)
        Matrix Xty = X_t.multiply(y_target);

        // Step 5: Invert (X^T * X) and solve for coefficients beta (Joshua's work)
        Matrix XtX_inverse = XtX.compute_inverse();
        coefficients = XtX_inverse.multiply(Xty);
    }

    Matrix PolynomialRegression::predict(const Matrix& X_input) const {
        Matrix design_matrix = FeatureExpansion::create_polynomial_features(X_input, degree);
        return design_matrix.multiply(coefficients);
    }

    double PolynomialRegression::calculate_mse(const Matrix& y_true, const Matrix& y_pred) const {
        int n = y_true.get_rows();
        double sum_squared_error = 0.0;
        for (int i = 0; i < n; ++i) {
            double diff = y_true.at(i, 0) - y_pred.at(i, 0);
            sum_squared_error += (diff * diff);
        }
        return sum_squared_error / static_cast<double>(n);
    }

    double PolynomialRegression::calculate_rmse(const Matrix& y_true, const Matrix& y_pred) const {
        return std::sqrt(calculate_mse(y_true, y_pred));
    }

    Matrix PolynomialRegression::get_coefficients() const {
        return coefficients;
    }
}