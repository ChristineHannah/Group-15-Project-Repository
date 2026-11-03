#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "poly_reg/matrix.hpp"
#include "poly_reg/polynomial_regression.hpp"

// HELPER FUNCTION: Floating-Point Comparison
// Safely checks closeness of fit parameters.

bool is_nearly_equal(double calculated_val, double expected_val, double tolerance = 1e-3)
{
    return std::fabs(calculated_val - expected_val) < tolerance;
}

//TEST: Degree 1 Linear Fit Integration Test
// Fits a linear model (degree 1) to a straight line dataset (y = 2x + 1) and 
// verifies the extracted intercept and slope weights.
void test_linear_fit_degree_1()
{
    using namespace PolyReg;
    // Perfect line y = 2x + 1
    Matrix X_data({{1.0}, {2.0}, {3.0}, {4.0}});
    Matrix y_data({{3.0}, {5.0}, {7.0}, {9.0}});

    PolynomialRegression model(1);
    model.fit(X_data, y_data);

    Matrix weights = model.get_coefficients();
    assert(weights.get_rows() == 2);
    assert(is_nearly_equal(weights.at(0, 0), 1.0)); // Intercept
    assert(is_nearly_equal(weights.at(1, 0), 2.0)); // Slope
    std::cout << "[PASS] Degree 1 Linear Fit Integration Test\n";
}

// TEST: Degree 2 Quadratic Fit Integration Test
// Fits a quadratic model (degree 2) to a parabolic dataset (y = x^2 + 2x + 3) 
// and evaluates the prediction Mean Squared Error (MSE)
void test_quadratic_fit_degree_2()
{
    using namespace PolyReg;
    // Perfect parabola y = x^2 + 2x + 3
    Matrix X_data({{-2.0}, {-1.0}, {0.0}, {1.0}, {2.0}});
    Matrix y_data({{3.0}, {2.0}, {3.0}, {6.0}, {11.0}});

    PolynomialRegression model(2);
    model.fit(X_data, y_data);

    Matrix predictions = model.predict(X_data);

    // Calculated directly via the trained model's member function
    double mse = model.calculate_mse(y_data, predictions);

    assert(is_nearly_equal(mse, 0.0, 1e-4));
    std::cout << "[PASS] Degree 2 Quadratic Fit Integration Test\n";
}

// MAIN FUNCTION: Runs polynomial regression integration tests
int main()
{
    std::cout << "--- Running Complete Polynomial Regression Integration Test Suite ---\n";
    try
    {
        test_linear_fit_degree_1();
        test_quadratic_fit_degree_2();
        std::cout << "\nAll Regression Integration Tests Passed Successfully!\n\n";
    }
    catch (const std::exception &error)
    {
        std::cerr << "[FAIL] Integration test suite encountered error: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}