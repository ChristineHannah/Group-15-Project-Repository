#include "poly_reg/polynomial_regression.hpp"
#include "poly_reg/feature_expansion.hpp"
#include <stdexcept>
#include <cmath>

namespace PolyReg
{
    PolynomialRegression::PolynomialRegression(int degree)
        : polynomial_degree(degree), weight_coefficients()
    {
        if (degree < 1)
        {
            throw std::invalid_argument("Error: Polynomial degree must be at least 1.");
        }
    }

    Matrix PolynomialRegression::compute_normal_matrix_product(const Matrix &design_matrix) const
    {
        Matrix transposed_design = design_matrix.transpose();
        return transposed_design.multiply(design_matrix);
    }

    Matrix PolynomialRegression::compute_normal_vector_product(const Matrix &design_matrix, const Matrix &target_vector) const
    {
        Matrix transposed_design = design_matrix.transpose();
        return transposed_design.multiply(target_vector);
    }

    Matrix PolynomialRegression::compute_cost_gradient(const Matrix &design_matrix, const Matrix &target_vector, const Matrix &predictions) const
    {
        int total_samples = design_matrix.get_rows();
        Matrix error_residual = predictions.subtract(target_vector);
        Matrix transposed_design = design_matrix.transpose();
        Matrix raw_gradient = transposed_design.multiply(error_residual);
        return raw_gradient.scalar_multiply(2.0 / static_cast<double>(total_samples));
    }

    double PolynomialRegression::compute_total_cost(const Matrix &target_vector, const Matrix &predictions) const
    {
        int total_samples = target_vector.get_rows();
        double squared_sum = 0.0;
        for (int r = 0; r < total_samples; ++r)
        {
            double diff = target_vector.at(r, 0) - predictions.at(r, 0);
            squared_sum += (diff * diff);
        }
        return squared_sum / (2.0 * static_cast<double>(total_samples));
    }

    // Joshua's OLS Normal Equations Fit: beta = (X^T * X)^-1 * X^T * y
    void PolynomialRegression::fit(const Matrix &input_features, const Matrix &target_values)
    {
        if (input_features.get_rows() != target_values.get_rows())
        {
            throw std::invalid_argument("Error: Row mismatch between input features and target vector.");
        }

        Matrix design_matrix = FeatureExpansion::create_polynomial_features(input_features, polynomial_degree);
        Matrix normal_matrix = compute_normal_matrix_product(design_matrix);
        Matrix normal_vector = compute_normal_vector_product(design_matrix, target_values);

        Matrix inverted_coefficients = normal_matrix.compute_inverse();
        weight_coefficients = inverted_coefficients.multiply(normal_vector);
    }

    // Joshua's Gradient Descent Fit Loop
    void PolynomialRegression::fit_gradient_descent(const Matrix &input_features, const Matrix &target_values, double learning_rate, int epochs)
    {
        if (input_features.get_rows() != target_values.get_rows())
        {
            throw std::invalid_argument("Error: Row mismatch between features and targets for Gradient Descent.");
        }

        Matrix design_matrix = FeatureExpansion::create_polynomial_features(input_features, polynomial_degree);
        int feature_columns = design_matrix.get_cols();

        weight_coefficients = Matrix(feature_columns, 1, 0.0);

        for (int epoch = 0; epoch < epochs; ++epoch)
        {
            Matrix predictions = design_matrix.multiply(weight_coefficients);
            Matrix gradient = compute_cost_gradient(design_matrix, target_values, predictions);
            Matrix scaled_gradient = gradient.scalar_multiply(learning_rate);
            weight_coefficients = weight_coefficients.subtract(scaled_gradient);
        }
    }

    Matrix PolynomialRegression::predict(const Matrix &input_features) const
    {
        if (weight_coefficients.get_rows() == 0)
        {
            throw std::runtime_error("Error: Model must be trained using fit() or fit_gradient_descent() before making predictions.");
        }
        Matrix design_matrix = FeatureExpansion::create_polynomial_features(input_features, polynomial_degree);
        return design_matrix.multiply(weight_coefficients);
    }

    // Tatiana's Week 3 Evaluation Metrics
    double PolynomialRegression::calculate_mse(const Matrix &y_true, const Matrix &y_pred) const
    {
        if (y_true.get_rows() != y_pred.get_rows())
        {
            throw std::invalid_argument("Error: Dimension mismatch between true and predicted targets.");
        }
        int n = y_true.get_rows();
        if (n == 0)
            throw std::invalid_argument("Error: Cannot calculate MSE on empty matrices.");

        double sum_squared_error = 0.0;
        for (int i = 0; i < n; ++i)
        {
            double diff = y_true.at(i, 0) - y_pred.at(i, 0);
            sum_squared_error += (diff * diff);
        }
        return sum_squared_error / static_cast<double>(n);
    }

    double PolynomialRegression::calculate_rmse(const Matrix &y_true, const Matrix &y_pred) const
    {
        return std::sqrt(calculate_mse(y_true, y_pred));
    }

    // Tatiana's Week 4 Convergence Loss Tracker Implementation
    double PolynomialRegression::calculate_final_convergence_loss(const Matrix &X_input, const Matrix &y_target) const
    {
        Matrix preds = predict(X_input);
        return calculate_mse(y_target, preds);
    }

    int PolynomialRegression::get_degree() const
    {
        return polynomial_degree;
    }

    Matrix PolynomialRegression::get_coefficients() const
    {
        return weight_coefficients;
    }
} // namespace PolyReg