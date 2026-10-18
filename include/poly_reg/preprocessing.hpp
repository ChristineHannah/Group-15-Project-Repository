#pragma once

#include <utility>
#include "poly_reg/matrix.hpp"

namespace PolyReg {

class Preprocessing {
public:
    /**
     * Scales feature columns to the range [0, 1] using Min-Max normalization.
     */
    static Matrix compute_min_max_scaling(const Matrix& input_feature_matrix);

    /**
     * Standardizes feature columns to have a mean of 0 and standard deviation of 1 (Z-score).
     */
    static Matrix compute_z_score_standardization(const Matrix& input_feature_matrix);

    /**
     * Splits a dataset matrix into training and testing subsets based on the provided proportion (e.g., 0.8 for 80%).
     */
    static std::pair<Matrix, Matrix> split_train_test_data(const Matrix& dataset_matrix, double training_proportion);
};

} // namespace PolyReg