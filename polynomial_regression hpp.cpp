// include/poly_reg/polynomial_regression.hpp (Arnold's Base Version)
#pragma once
#include "poly_reg/matrix.hpp"
#include <utility>

namespace PolyReg {
    class PolynomialRegression {
    protected:
        int degree;
        Matrix coefficients; // Stores regression weights (beta)

    public:
        explicit PolynomialRegression(int poly_degree);

        // Arnold's core normal equation formulation steps
        Matrix compute_transpose_product(const Matrix& X) const;
        Matrix compute_normal_equation_rhs(const Matrix& X, const Matrix& y) const;

        // Virtual placeholder for Joshua to override/complete
        virtual void fit(const Matrix& X, const Matrix& y) = 0;
        Matrix predict(const Matrix& X) const;
    };
}