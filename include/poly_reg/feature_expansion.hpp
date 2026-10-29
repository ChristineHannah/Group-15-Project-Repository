#pragma once
#include "poly_reg/matrix.hpp"

namespace PolyReg
{
    class FeatureExpansion
    {
    public:
        /**
         * Converts a 1D or multi-variable input feature matrix into a polynomial design matrix
         * containing powers up to the specified degree: [1, x, x^2, x^3, ..., x^d].
         */
        static Matrix create_polynomial_features(const Matrix &input_feature_matrix, int polynomial_degree);
    };
} // namespace PolyReg