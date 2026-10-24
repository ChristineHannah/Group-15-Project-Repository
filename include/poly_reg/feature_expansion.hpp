#pragma once
#include "poly_reg/matrix.hpp"

namespace PolyReg {
class FeatureExpansion {
public:
    /**
     * Converts a 1D or multi-variable input feature matrix into a polynomial design matrix.
     * The result starts with a bias column, followed by each feature raised to powers 1 through the requested degree.
     * For one input feature, the columns are [1, x, x^2, ..., x^d].
     */
    static Matrix create_polynomial_features(const Matrix& input_feature_matrix, int polynomial_degree);
};
} // namespace PolyReg
