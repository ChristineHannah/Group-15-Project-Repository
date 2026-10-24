#pragma once
#include "poly_reg/matrix.hpp"

namespace PolyReg
{
    class PolynomialRegression
    {
    private:
        int polynomial_degree;
        Matrix weight_coefficients; // Final solved regression weights (beta)
    public:
        explicit PolynomialRegression(int degree = 1);

        // Arnold's Base Matrix Product Methods (OLS Formulations)
        Matrix compute_normal_matrix_product(const Matrix &design_matrix) const;
        Matrix compute_normal_vector_product(const Matrix &design_matrix, const Matrix &target_vector) const;

        // Arnold's Gradient Descent Cost & Gradient Helpers
        Matrix compute_cost_gradient(const Matrix &design_matrix, const Matrix &target_vector, const Matrix &predictions) const;
        double compute_total_cost(const Matrix &target_vector, const Matrix &predictions) const;

        // Joshua's Model Fitting Solvers (OLS Normal Equations & Gradient Descent)
        void fit(const Matrix &input_features, const Matrix &target_values);
        void fit_gradient_descent(const Matrix &input_features, const Matrix &target_values, double learning_rate, int epochs);
        Matrix predict(const Matrix &input_features) const;

        // Tatiana's Week 3 Evaluation Metrics (MSE & RMSE)
        double calculate_mse(const Matrix &y_true, const Matrix &y_pred) const;
        double calculate_rmse(const Matrix &y_true, const Matrix &y_pred) const;

        // Tatiana's Week 4 Convergence Loss Tracker
        double calculate_final_convergence_loss(const Matrix &X_input, const Matrix &y_target) const;

        // Getters
        int get_degree() const;
        Matrix get_coefficients() const;
    };
} // namespace PolyReg