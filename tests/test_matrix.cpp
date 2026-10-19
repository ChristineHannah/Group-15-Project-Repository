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

void test_matrix_addition() {
    using namespace PolyReg;

    Matrix matrix_a({
        {1.0, 2.0},
        {3.0, 4.0}
    });

    Matrix matrix_b({
        {5.0, 6.0},
        {7.0, 8.0}
    });

    Matrix sum_result = matrix_a.add(matrix_b);

    assert(sum_result.get_rows() == 2);
    assert(sum_result.get_cols() == 2);
    assert(is_nearly_equal(sum_result.at(0, 0), 6.0));
    assert(is_nearly_equal(sum_result.at(0, 1), 8.0));
    assert(is_nearly_equal(sum_result.at(1, 0), 10.0));
    assert(is_nearly_equal(sum_result.at(1, 1), 12.0));

    std::cout << "[PASS] Matrix Addition Test\n";
}

void test_matrix_multiplication() {
    using namespace PolyReg;

    Matrix matrix_a({
        {1.0, 2.0},
        {3.0, 4.0}
    });

    Matrix matrix_b({
        {2.0, 0.0},
        {1.0, 2.0}
    });

    Matrix product_result = matrix_a.multiply(matrix_b);

    assert(product_result.get_rows() == 2);
    assert(product_result.get_cols() == 2);
    // [1*2 + 2*1, 1*0 + 2*2] = [4, 4]
    // [3*2 + 4*1, 3*0 + 4*2] = [10, 8]
    assert(is_nearly_equal(product_result.at(0, 0), 4.0));
    assert(is_nearly_equal(product_result.at(0, 1), 4.0));
    assert(is_nearly_equal(product_result.at(1, 0), 10.0));
    assert(is_nearly_equal(product_result.at(1, 1), 8.0));

    std::cout << "[PASS] Matrix Multiplication Test\n";
}

void test_matrix_transpose() {
    using namespace PolyReg;

    Matrix original_matrix({
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    });

    Matrix transposed_matrix = original_matrix.transpose();

    assert(transposed_matrix.get_rows() == 3);
    assert(transposed_matrix.get_cols() == 2);
    assert(is_nearly_equal(transposed_matrix.at(0, 0), 1.0));
    assert(is_nearly_equal(transposed_matrix.at(0, 1), 4.0));
    assert(is_nearly_equal(transposed_matrix.at(2, 1), 6.0));

    std::cout << "[PASS] Matrix Transpose Test\n";
}

void test_matrix_determinant_and_inverse() {
    using namespace PolyReg;

    // 2x2 Matrix: [[4.0, 7.0], [2.0, 6.0]]
    // Determinant = (4*6) - (7*2) = 24 - 14 = 10.0
    Matrix square_matrix({
        {4.0, 7.0},
        {2.0, 6.0}
    });

    double det = square_matrix.compute_determinant();
    assert(is_nearly_equal(det, 10.0));

    Matrix inverted_matrix = square_matrix.compute_inverse();
    assert(inverted_matrix.get_rows() == 2);
    assert(inverted_matrix.get_cols() == 2);

    // Verify A * A^-1 equals Identity Matrix [[1, 0], [0, 1]]
    Matrix identity_check = square_matrix.multiply(inverted_matrix);
    assert(is_nearly_equal(identity_check.at(0, 0), 1.0));
    assert(is_nearly_equal(identity_check.at(0, 1), 0.0));
    assert(is_nearly_equal(identity_check.at(1, 0), 0.0));
    assert(is_nearly_equal(identity_check.at(1, 1), 1.0));

    std::cout << "[PASS] Matrix Determinant and Inverse Test\n";
}

void test_matrix_exceptions() {
    using namespace PolyReg;

    Matrix matrix_a(2, 2, 1.0);
    Matrix matrix_b(3, 3, 2.0);

    // Test dimension mismatch exception in addition
    bool addition_exception_caught = false;
    try {
        matrix_a.add(matrix_b);
    } catch (const std::invalid_argument&) {
        addition_exception_caught = true;
    }
    assert(addition_exception_caught);

    // Test out of bounds index exception
    bool out_of_bounds_caught = false;
    try {
        matrix_a.at(5, 5);
    } catch (const std::out_of_range&) {
        out_of_bounds_caught = true;
    }
    assert(out_of_bounds_caught);

    std::cout << "[PASS] Matrix Exception Handling Test\n";
}

int main() {
    std::cout << "--- Running Matrix Unit Tests ---" << std::endl;
    try {
        test_matrix_construction_and_access();
        test_matrix_addition();
        test_matrix_multiplication();
        test_matrix_transpose();
        test_matrix_determinant_and_inverse();
        test_matrix_exceptions();
        std::cout << "\nAll Matrix Unit Tests Passed Successfully!\n" << std::endl;
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] Test suite failed with unhandled exception: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}