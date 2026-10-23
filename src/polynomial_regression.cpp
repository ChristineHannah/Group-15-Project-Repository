// src/polynomial_regression.cpp (Arnold & Joshua Merged Implementation)
#include "poly_reg/polynomial_regression.hpp"
#include "poly_reg/feature_expansion.hpp"
#include <stdexcept>

namespace PolyReg {
PolynomialRegression::PolynomialRegression(int degree) : polynomial_degree(degree), weight_coefficients() {}

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
        Matrix scaled_gradient = gradient.scalar_multiply(learning_rate);
        weight_coefficients = weight_coefficients.subtract(scaled_gradient);
    }
}

Matrix PolynomialRegression::get_coefficients() const {
    return weight_coefficients;
}
} // namespace PolyReg