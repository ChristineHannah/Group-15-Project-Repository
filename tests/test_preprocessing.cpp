#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <utility>
#include "poly_reg/matrix.hpp"
#include "poly_reg/preprocessing.hpp"

// Helper function for safe floating-point comparison
bool is_nearly_equal(double calculated_val, double expected_val, double tolerance = 1e-5) {
    return std::fabs(calculated_val - expected_val) < tolerance;
}

void test_min_max_scaling() {
    using namespace PolyReg;

    // Single feature column with values [10.0, 20.0, 30.0]
    Matrix input_data({
        {10.0},
        {20.0},
        {30.0}
    });

    Matrix scaled_data = Preprocessing::compute_min_max_scaling(input_data);

    assert(scaled_data.get_rows() == 3);
    assert(scaled_data.get_cols() == 1);
    // Min (10) -> 0.0, Mid (20) -> 0.5, Max (30) -> 1.0
    assert(is_nearly_equal(scaled_data.at(0, 0), 0.0));
    assert(is_nearly_equal(scaled_data.at(1, 0), 0.5));
    assert(is_nearly_equal(scaled_data.at(2, 0), 1.0));

    std::cout << "[PASS] Min-Max Scaling Test\n";
}

void test_z_score_standardization() {
    using namespace PolyReg;

    // Dataset column: [1.0, 2.0, 3.0, 4.0, 5.0]
    // Mean = 3.0
    Matrix input_data({
        {1.0},
        {2.0},
        {3.0},
        {4.0},
        {5.0}
    });

    Matrix standardized_data = Preprocessing::compute_z_score_standardization(input_data);

    assert(standardized_data.get_rows() == 5);
    assert(standardized_data.get_cols() == 1);

    // After standardization, the mean of the column should be approximately 0.0
    double column_sum = 0.0;
    for (int r = 0; r < standardized_data.get_rows(); ++r) {
        column_sum += standardized_data.at(r, 0);
    }
    double calculated_mean = column_sum / static_cast<double>(standardized_data.get_rows());

    assert(is_nearly_equal(calculated_mean, 0.0));

    std::cout << "[PASS] Z-Score Standardization Test\n";
}

void test_train_test_split() {
    using namespace PolyReg;

    // Create a dataset with 10 rows and 2 columns
    Matrix dataset(10, 2, 5.0);

    // Split 80% train / 20% test
    std::pair<Matrix, Matrix> split_result = Preprocessing::split_train_test_data(dataset, 0.8);
    Matrix train_set = split_result.first;
    Matrix test_set = split_result.second;

    assert(train_set.get_rows() == 8);
    assert(train_set.get_cols() == 2);
    assert(test_set.get_rows() == 2);
    assert(test_set.get_cols() == 2);

    std::cout << "[PASS] Train/Test Split Test\n";
}

int main() {
    std::cout << "--- Running Preprocessing Unit Tests ---" << std::endl;
    try {
        test_min_max_scaling();
        test_z_score_standardization();
        test_train_test_split();
        std::cout << "\nAll Preprocessing Unit Tests Passed Successfully!\n" << std::endl;
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] Preprocessing test failed with exception: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}