#include "poly_reg/feature_expansion.hpp"
#include <stdexcept>
#include <cmath>

namespace PolyReg {

Matrix FeatureExpansion::create_polynomial_features(const Matrix& input_feature_matrix, int polynomial_degree) {
    int total_rows = input_feature_matrix.get_rows();
    int total_cols = input_feature_matrix.get_cols();

    if (total_rows == 0 || total_cols == 0) {
        throw std::invalid_argument("Error: Cannot perform feature expansion on an empty input matrix.");
    }

    if (polynomial_degree < 1) {
        throw std::invalid_argument("Error: Polynomial degree must be at least 1.");
    }

    // For single-variable input (1D vector represented as N x 1 matrix),
    // the design matrix will have (degree + 1) columns: [1, x, x^2, ..., x^d]
    // For general implementation with 1 input column, output columns = degree + 1.
    int output_column_count = (total_cols * polynomial_degree) + 1;

    Matrix design_matrix(total_rows, output_column_count, 0.0);

    for (int row_idx = 0; row_idx < total_rows; ++row_idx) {
        // Column 0 is always the bias term (1.0)
        design_matrix.at(row_idx, 0) = 1.0;

        int current_col_tracker = 1;

        // Iterate through each original input feature column
        for (int col_idx = 0; col_idx < total_cols; ++col_idx) {
            double feature_value = input_feature_matrix.at(row_idx, col_idx);
            double running_power = feature_value;

            // Generate polynomial powers from 1 up to the target degree: x^1, x^2, ..., x^d
            for (int degree = 1; degree <= polynomial_degree; ++degree) {
                design_matrix.at(row_idx, current_col_tracker++) = running_power;
                if (degree < polynomial_degree) {
                    running_power *= feature_value;
                }
            }
        }
    }

    return design_matrix;
}

} // namespace PolyReg
