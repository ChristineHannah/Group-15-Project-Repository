// tests/test_gradient_descent.cpp (Joseph's New Test File)
#include <iostream>
#include <cassert>
#include <cmath>
#include "poly_reg/matrix.hpp"
#include "poly_reg/polynomial_regression.hpp"

bool is_close_val(double a, double b, double tol = 1e-2) {
    return std::fabs(a - b) < tol;
}

void test_gradient_descent_convergence() {
    using namespace PolyReg;
    // Simple linear dataset y = 3x + 2
    Matrix X_data({{1.0}, {2.0}, {3.0}, {4.0}});
    Matrix y_data({{5.0}, {8.0}, {11.0}, {14.0}});

    PolynomialRegression gd_model(1);
    gd_model.fit_gradient_descent(X_data, y_data, 0.01, 1500);

    Matrix weights = gd_model.get_coefficients();
    assert(weights.get_rows() == 2);
    
    // Verify weights converge close to intercept = 2.0, slope = 3.0
    assert(is_close_val(weights.at(0, 0), 2.0, 0.2));
    assert(is_close_val(weights.at(1, 0), 3.0, 0.2));

    std::cout << "[PASS] Gradient Descent Convergence Integration Test\n";
}

int main() {
    std::cout << "--- Running Gradient Descent Test Suite ---\n";
    try {
        test_gradient_descent_convergence();
        std::cout << "\nAll Gradient Descent Tests Passed Successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "[FAIL] Test failed: " << e.what() << "\n";
        return 1;
    }
    return 0;
}