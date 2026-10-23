// include/poly_reg/polynomial_regression.hpp (Arnold & Joshua Merged Final)
#pragma once
#include "poly_reg/matrix.hpp"

namespace PolyReg {
class PolynomialRegression {
private:
    int polynomial_degree;
    Matrix weight_coefficients;
public:
    explicit PolynomialRegression(int degree = 1);

    // OLS Normal Equations Fit (Week 3)
    void fit(const Matrix& input_features, const Matrix& target_values);

    // Gradient Descent Fit (Week 4 - Joshua & Arnold)
    void fit_gradient_descent(const Matrix& input_features, const Matrix& target_values, double learning_rate, int epochs);

    Matrix predict(const Matrix& input_features) const;
    Matrix get_coefficients() const;
};
} // namespace PolyReg