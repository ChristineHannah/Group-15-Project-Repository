#pragma once

#include <utility>
#include "poly_reg/matrix.hpp"

namespace PolyReg
{

    class Preprocessing
    {
    public:
        // Scales feature columns to the range [0, 1] using Min-Max normalization.
        //  ensures that features with massive raw numbers such as 500, 600004, do not over power smaller ones like 45, 60 during machine learning calculations.
        //  used when data needs to be locked inside strict bounds like 0 and 1.
        static Matrix compute_min_max_scaling(const Matrix &input_feature_matrix);

        // Standardizes feature columns to have a mean of 0 and standard deviation of 1 (Z-score).
        // used in like gradient descent because centered symmetrically distributed data helps the model converge to find the best curve weights much faster.
        static Matrix compute_z_score_standardization(const Matrix &input_feature_matrix);

        // Splits a dataset matrix into training and testing subsets based on the provided proportion (e.g., 0.8 for 80%).

        static std::pair<Matrix, Matrix> split_train_test_data(const Matrix &dataset_matrix, double training_proportion);
        // std:: pair bundles exactly two items together into a single neat package.
        // used because normally a C++ function can only return on single thing.
        // when called, the function returns a pair of matices, one for the training set and the other for the testing set.
    };

} // namespace PolyReg
// without static, to use a function, one would have to create an object vraiable in memory.
// static is used such that one does not have to create any object variable. One can call the function directly using the class name, e.g., Preprocessing::compute_min_max_scaling(matrix). This is useful for utility functions that don't need to maintain any state between calls.