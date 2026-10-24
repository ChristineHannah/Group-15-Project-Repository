// include/poly_reg/polynomial_regression.hpp (Arnold & Joshua Merged Final)
#pragma once
#include "poly_reg/matrix.hpp"

namespace PolyReg {
class PolynomialRegression {
private:
    int polynomial_degree;
    Matrix weight_coefficients;

    //helper method for gradient decent cost gradient calculation
    Matrix compute_cost_gradient(const Matrix& design_matrix, const Matrix& target_values, const Matrix& predictions) const;
public:
    explicit PolynomialRegression(int degree = 1);

    // OLS Normal Equations Fit (Week 3)
    void fit(const Matrix& input_features, const Matrix& target_values);

    // Gradient Descent Fit (Week 4 - Joshua & Arnold)
    void fit_gradient_descent(const Matrix& input_features, const Matrix& target_values, double learning_rate, int epochs);

    Matrix predict(const Matrix& input_features) const;
    Matrix get_coefficients() const;
};

class RegressionMetrics {
public:
    /**
     * Calculates Mean Squared Error (MSE) between true target values and predicted values.
     * Formula: MSE = (1 / n) * sum((y_true - y_pred)^2)
     */
    static double compute_mean_squared_error(const Matrix& y_true, const Matrix& y_pred);

    /**
     * Calculates Root Mean Squared Error (RMSE).
     * Formula: RMSE = sqrt(MSE)
     */
    static double compute_root_mean_squared_error(const Matrix& y_true, const Matrix& y_pred);
};
} // namespace PolyReg