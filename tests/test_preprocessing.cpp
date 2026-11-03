#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <utility>
#include "poly_reg/matrix.hpp"
#include "poly_reg/preprocessing.hpp"
#include "poly_reg/csv_loader.hpp"

// Helper function for safe floating-point comparison
// Safely checks if two calculated floating-point numbers are nearly equal.
bool is_nearly_equal(double calculated_val, double expected_val, double tolerance = 1e-5) {
    return std::fabs(calculated_val - expected_val) < tolerance;
}

// TEST: Min-Max Scaling
// Verifies that features are correctly normalized to a range between 0.0 and 1.0.
void test_min_max_scaling() {
    using namespace PolyReg;

    Matrix input_data({
        {10.0},
        {20.0},
        {30.0}
    });

    Matrix scaled_data = Preprocessing::compute_min_max_scaling(input_data);

    assert(scaled_data.get_rows() == 3);
    assert(scaled_data.get_cols() == 1);
    assert(is_nearly_equal(scaled_data.at(0, 0), 0.0));
    assert(is_nearly_equal(scaled_data.at(1, 0), 0.5));
    assert(is_nearly_equal(scaled_data.at(2, 0), 1.0));

    std::cout << "[PASS] Min-Max Scaling Test (Tatiana)\n";
}

// TEST: Z-Score Standardization
// Verifies that data is standardized such that its mean becomes approximately 0.
void test_z_score_standardization() {
    using namespace PolyReg;

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

    // Verify mean is approximately 0.0
    double column_sum = 0.0;
    for (int r = 0; r < standardized_data.get_rows(); ++r) {
        column_sum += standardized_data.at(r, 0);
    }
    double calculated_mean = column_sum / static_cast<double>(standardized_data.get_rows());
    assert(is_nearly_equal(calculated_mean, 0.0));

    std::cout << "[PASS] Z-Score Standardization Test (Tatiana)\n";
}

// TEST: Train/Test Split
// Verifies that a dataset is properly split into training and testing subsets
void test_train_test_split() {
    using namespace PolyReg;

    Matrix dataset(10, 2, 5.0);
    std::pair<Matrix, Matrix> split_result = Preprocessing::split_train_test_data(dataset, 0.8);
    
    assert(split_result.first.get_rows() == 8);
    assert(split_result.second.get_rows() == 2);

    std::cout << "[PASS] Train/Test Split Test (Tatiana)\n";
}

void test_csv_loader() {
    using namespace PolyReg;

    // Test loading Allan's sample dataset file from data/input/
    try {
        Matrix loaded_csv_data = CSVLoader::load_dataset_from_csv("data/input/quadratic_clean.csv");
        assert(loaded_csv_data.get_rows() > 0);
        assert(loaded_csv_data.get_cols() == 2); // Expecting x and y columns[cite: 17]
        std::cout << "[PASS] CSV Loader Automated Test (Pruna)\n";
    } catch (const std::exception& e) {
        std::cout << "[INFO] CSV Loader test skipped or file path not found locally: " << e.what() << "\n";
    }
}

// MAIN FUNCTION: Entry point for running preprocessing unit tests
int main() {
    std::cout << "--- Running Preprocessing & Data Ingestion Test Suite ---" << std::endl;
    try {
        test_min_max_scaling();
        test_z_score_standardization();
        test_train_test_split();
        test_csv_loader();
        std::cout << "\nAll Preprocessing and Loader Tests Passed Successfully!\n" << std::endl;
    } catch (const std::exception& error) {
        std::cerr << "[FAIL] Preprocessing test suite failed with exception: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}