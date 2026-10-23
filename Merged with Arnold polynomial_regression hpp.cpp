// include/poly_reg/polynomial_regression.hpp (Arnold & Joshua Merged)
#pragma once
#include "poly_reg/matrix.hpp"

namespace PolyReg {
    class PolynomialRegression {
    private:
        int degree;
        Matrix coefficients; // Final solved weights beta

    public:
        explicit PolynomialRegression(int poly_degree);

        // Fits the model using Ordinary Least Squares (OLS) Normal Equations
        void fit(const Matrix& X_input, const Matrix& y_target);

        // Predicts target values for new inputs
        Matrix predict(const Matrix& X_input) const;

        // Evaluation metrics (Tatiana's integration)
        double calculate_mse(const Matrix& y_true, const Matrix& y_pred) const;
        double calculate_rmse(const Matrix& y_true, const Matrix& y_pred) const;

        Matrix get_coefficients() const;
    };
}