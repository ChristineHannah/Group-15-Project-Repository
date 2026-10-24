// src/polynomial_regression.cpp (Arnold & Joshua Merged Implementation)
#include "poly_reg/polynomial_regression.hpp"
#include "poly_reg/feature_expansion.hpp"
#include <stdexcept>

namespace PolyReg {
PolynomialRegression::PolynomialRegression(int degree) : polynomial_degree(degree), weight_coefficients(0,0) {}

void PolynomialRegression::fit_gradient_descent(const Matrix& input_features, const Matrix& target_values, double learning_rate, int epochs) {
    if (input_features.get_rows() != target_values.get_rows()) {
        throw std::invalid_argument("Error: Row mismatch between features and targets for Gradient Descent.");
    }

    Matrix design_matrix = FeatureExpansion::create_polynomial_features(input_features, polynomial_degree);
    int feature_columns = design_matrix.get_cols();

    // Initialize weights to zero
    weight_coefficients = Matrix(feature_columns, 1, 0.0);

    // Iterative Gradient Descent loop
    for (int epoch = 0; epoch < epochs; ++epoch) {
        Matrix predictions = design_matrix.multiply(weight_coefficients);
        Matrix gradient = compute_cost_gradient(design_matrix, target_values, predictions);

        // Update weights: beta = beta - (learning_rate * gradient)
        Matrix scaled_gradient = gradient.multiply(learning_rate);
        weight_coefficients = weight_coefficients.subtract(scaled_gradient);
    }
}

Matrix PolynomialRegression::get_coefficients() const {
    return weight_coefficients;
}

double RegressionMetrics::compute_mean_squared_error(const Matrix& y_true, const Matrix& y_pred) {
    if (y_true.get_rows() != y_pred.get_rows() || y_true.get_cols() != y_pred.get_cols()) {
        throw std::invalid_argument("Error: Dimension mismatch between true and predicted target values.");
    }
    
    int total_observations = y_true.get_rows();
    if (total_observations == 0) {
        throw std::invalid_argument("Error: Cannot calculate MSE on empty matrices.");
    }

    double accumulated_squared_error = 0.0;
    for (int r = 0; r < total_observations; ++r) {
        double residual_difference = y_true.at(r, 0) - y_pred.at(r, 0);
        accumulated_squared_error += residual_difference * residual_difference;
    }

    return accumulated_squared_error / static_cast<double>(total_observations);
}

double RegressionMetrics::compute_root_mean_squared_error(const Matrix& y_true, const Matrix& y_pred) {
    double mse_value = compute_mean_squared_error(y_true, y_pred);
    return std::sqrt(mse_value);
}
} // namespace PolyReg