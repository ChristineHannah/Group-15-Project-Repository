#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "poly_reg/matrix.hpp"

// Helper function for safe floating-point comparison
bool is_nearly_equal(double calculated_val, double expected_val, double tolerance = 1e-5) {
    return std::fabs(calculated_val - expected_val) < tolerance;
}

void test_matrix_construction_and_access() {
    using namespace PolyReg;

    Matrix custom_matrix({
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    });

    assert(custom_matrix.get_rows() == 2);
    assert(custom_matrix.get_cols() == 3);
    assert(is_nearly_equal(custom_matrix.at(0, 0), 1.0));
    assert(is_nearly_equal(custom_matrix.at(1, 2), 6.0));

    std::cout << "[PASS] Matrix Construction and Element Access Test\n";
}

void test_matrix_arithmetic() {
    using namespace PolyReg;

    Matrix matrix_a({
        {1.0, 2.0},
        {3.0, 4.0}
    });

    Matrix matrix_b({
        {5.0, 6.0},
        {7.0, 8.0}
    });

    // Test Addition (Arnold)
    Matrix sum_result = matrix_a.add(matrix_b);
    assert(is_nearly_equal(sum_result.at(0, 0), 6.0));
    assert(is_nearly_equal(sum_result.at(1, 1), 12.0));

    // Test Subtraction (Arnold)
    Matrix diff_result = matrix_b.subtract(matrix_a);
    assert(is_nearly_equal(diff_result.at(0, 0), 4.0));
    assert(is_nearly_equal(diff_result.at(1, 1), 4.0));

    // Test Multiplication (Arnold)
    Matrix product_result = matrix_a.multiply(matrix_b);
    assert(is_nearly_equal(product_result.at(0, 0), 19.0));
    assert(is_nearly_equal(product_result.at(1, 1), 50.0));

    // Test Transpose (Arnold)
    Matrix transposed = matrix_a.transpose();
    assert(transposed.get_rows() == 2 && transposed.get_cols() == 2);
    assert(is_nearly_equal(transposed.at(0, 1), 3.0));

    std::cout << "[PASS] Matrix Arithmetic and Transpose Tests\n";
}

void test_matrix_solvers_and_inversion() {
    using namespace PolyReg;

    // 2x2 Square Matrix: [[4.0, 7.0], [2.0, 6.0]]
    // Determinant = (4 * 6) - (7 * 2) = 24 - 14 = 10.0
    Matrix square_matrix({
        {4.0, 7.0},
        {2.0, 6.0}
    });

    // Test Determinant Calculation (Joshua)
    double calculated_det = square_matrix.compute_determinant();
    assert(is_nearly_equal(calculated_det, 10.0));

    // Test Matrix Inversion (Joshua)
    Matrix inverted_matrix = square_matrix.compute_inverse();
    assert(inverted_matrix.get_rows() == 2);
    assert(inverted_matrix.get_cols() == 2);

    // Verify A * A^-1 equals Identity Matrix [[1, 0], [0, 1]]
    Matrix identity_verification = square_matrix.multiply(inverted_matrix);
    assert(is_nearly_equal(identity_verification.at(0, 0), 1.0));
    assert(is_nearly_equal(identity_verification.at(0, 1), 0.0));
    assert(is_nearly_equal(identity_verification.at(1, 0), 0.0));
    assert(is_nearly_equal(identity_verification.at(1, 1), 1.0));

    std::cout << "[PASS] Matrix Determinant and Inversion Tests (Joshua)\n";
}

void test_matrix_exceptions() {
    using namespace PolyReg;

    Matrix matrix_a(2, 2, 1.0);
    Matrix matrix_b(3, 3, 2.0);

    // Dimension mismatch exception check
    bool exception_caught = false;
    try {
        matrix_a.add(matrix_b);
    } catch (const std::invalid_argument&) {
        exception_caught = true;
    }
    assert(exception_caught);

    // Singular matrix inversion exception check
    Matrix singular_matrix({
        {1.0, 2.0},
        {2.0, 4.0}
    });
    bool singular_exception_caught = false;
    try {
        singular_matrix.compute_inverse();
    } catch (const std::runtime_error&) {
        singular_exception_caught = true;
    }
    assert(singular_exception_caught);

    std::cout << "[PASS] Matrix Exception Handling Tests\n";
}

int main() {
    std::cout << "--- Running Complete Matrix Unit Test Suite ---" << std::endl;
    try {
        test_matrix_construction_and_access();
        test_matrix_arithmetic();
        test_matrix_solvers_and_inversion();
        test_matrix_exceptions();
        std::cout << "\nAll Matrix Tests Passed Successfully!\n" << std::endl;
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] Matrix test suite encountered an unexpected exception: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}