#include "poly_reg/preprocessing.hpp"
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <algorithm>

namespace PolyReg {

Matrix Preprocessing::compute_min_max_scaling(const Matrix& input_feature_matrix) {
    int total_rows = input_feature_matrix.get_rows();
    int total_cols = input_feature_matrix.get_cols();

    if (total_rows == 0 || total_cols == 0) {
        throw std::invalid_argument("Error: Cannot scale an empty matrix.");
    }

    Matrix scaled_matrix(total_rows, total_cols);

    // Compute Min-Max scaling independently for each feature column
    for (int col_idx = 0; col_idx < total_cols; ++col_idx) {
        double column_min = input_feature_matrix.at(0, col_idx);
        double column_max = input_feature_matrix.at(0, col_idx);

        // Find the minimum and maximum values in the current column
        for (int row_idx = 1; row_idx < total_rows; ++row_idx) {
            double current_value = input_feature_matrix.at(row_idx, col_idx);
            if (current_value < column_min) column_min = current_value;
            if (current_value > column_max) column_max = current_value;
        }

        double value_range = column_max - column_min;

        // Scale each value in the column to the range [0.0, 1.0]
        for (int row_idx = 0; row_idx < total_rows; ++row_idx) {
            double raw_value = input_feature_matrix.at(row_idx, col_idx);
            if (value_range == 0.0) {
                // Prevent division by zero if all values in the column are identical
                scaled_matrix.at(row_idx, col_idx) = 0.0;
            } else {
                scaled_matrix.at(row_idx, col_idx) = (raw_value - column_min) / value_range;
            }
        }
    }

    return scaled_matrix;
}

Matrix Preprocessing::compute_z_score_standardization(const Matrix& input_feature_matrix) {
    int total_rows = input_feature_matrix.get_rows();
    int total_cols = input_feature_matrix.get_cols();

    if (total_rows <= 1) {
        throw std::invalid_argument("Error: Insufficient rows for Z-score standardization (requires at least 2 rows).");
    }

    Matrix standardized_matrix(total_rows, total_cols);

    // Standardize each feature column independently
    for (int col_idx = 0; col_idx < total_cols; ++col_idx) {
        double column_sum = 0.0;

        // Step 1: Calculate the arithmetic mean (mu) for the column
        for (int row_idx = 0; row_idx < total_rows; ++row_idx) {
            column_sum += input_feature_matrix.at(row_idx, col_idx);
        }
        double column_mean = column_sum / static_cast<double>(total_rows);

        // Step 2: Calculate the sample standard deviation (sigma)
        double squared_difference_sum = 0.0;
        for (int row_idx = 0; row_idx < total_rows; ++row_idx) {
            double difference = input_feature_matrix.at(row_idx, col_idx) - column_mean;
            squared_difference_sum += (difference * difference);
        }
        double column_std_dev = std::sqrt(squared_difference_sum / static_cast<double>(total_rows - 1));

        // Step 3: Apply the Z-score transformation formula: (x - mean) / std_dev
        for (int row_idx = 0; row_idx < total_rows; ++row_idx) {
            double raw_value = input_feature_matrix.at(row_idx, col_idx);
            if (column_std_dev == 0.0) {
                standardized_matrix.at(row_idx, col_idx) = 0.0;
            } else {
                standardized_matrix.at(row_idx, col_idx) = (raw_value - column_mean) / column_std_dev;
            }
        }
    }

    return standardized_matrix;
}

std::pair<Matrix, Matrix> Preprocessing::split_train_test_data(const Matrix& dataset_matrix, double training_proportion) {
    int total_rows = dataset_matrix.get_rows();
    int total_cols = dataset_matrix.get_cols();

    if (training_proportion <= 0.0 || training_proportion >= 1.0) {
        throw std::invalid_argument("Error: Training proportion must be strictly between 0.0 and 1.0.");
    }

    int training_row_count = static_cast<int>(std::round(total_rows * training_proportion));
    int testing_row_count = total_rows - training_row_count;

    if (training_row_count == 0 || testing_row_count == 0) {
        throw std::runtime_error("Error: Dataset size is too small to perform the requested train/test split.");
    }

    Matrix training_subset(training_row_count, total_cols);
    Matrix testing_subset(testing_row_count, total_cols);

    // Populate the training subset matrix from the top portion of the dataset
    for (int row_idx = 0; row_idx < training_row_count; ++row_idx) {
        for (int col_idx = 0; col_idx < total_cols; ++col_idx) {
            training_subset.at(row_idx, col_idx) = dataset_matrix.at(row_idx, col_idx);
        }
    }

    // Populate the testing subset matrix from the remaining lower portion of the dataset
    for (int row_idx = 0; row_idx < testing_row_count; ++row_idx) {
        for (int col_idx = 0; col_idx < total_cols; ++col_idx) {
            testing_subset.at(row_idx, col_idx) = dataset_matrix.at(training_row_count + row_idx, col_idx);
        }
    }

    return {training_subset, testing_subset};
}

} // namespace PolyReg