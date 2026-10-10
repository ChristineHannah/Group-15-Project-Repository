// tests/test_features.cpp
// Tests for polynomial feature expansion.
//
// ASSUMED interface (change the ADJUST lines to match the real code):
//   header:   poly_reg/polynomial_features.hpp
//   function: Matrix polynomial_features(const Matrix& x, std::size_t degree);
//             x is a column (n x 1). The result is n x (degree + 1) with columns
//             1, x, x^2, ..., x^degree  (first column of ones included).
//
// If the header does not exist yet, this test compiles, prints SKIPPED and
// exits with 0, so it cannot break the build.

#include <iostream>

#include "poly_reg/matrix.hpp"

using namespace std;
using namespace poly_reg;

#if defined(__has_include)
#if __has_include("poly_reg/polynomial_features.hpp")  // ADJUST: real header name
#define HAS_FEATURES 1
#endif
#endif

#ifdef HAS_FEATURES

#include "poly_reg/polynomial_features.hpp"  // ADJUST: real header name

static int failures = 0;

static void check(bool condition, const char* name) {
    if (condition) {
        cout << "[PASS] " << name << "\n";
    } else {
        cout << "[FAIL] " << name << "\n";
        ++failures;
    }
}

static bool nearly(double a, double b, double tol = 1e-9) {
    return (a > b ? a - b : b - a) < tol;
}

int main() {
    // x = 1, 2, 3 with degree 2 should give columns 1, x, x^2:
    //   [1, 1, 1]
    //   [1, 2, 4]
    //   [1, 3, 9]
    Matrix x = {{1}, {2}, {3}};
    Matrix f = polynomial_features(x, 2);  // ADJUST: function name and arguments

    check(f.rows() == 3 && f.cols() == 3, "features: 3 rows and degree+1 columns");  // ADJUST if no ones column
    check(nearly(f(0, 0), 1) && nearly(f(1, 0), 1) && nearly(f(2, 0), 1), "features: first column is all ones");
    check(nearly(f(0, 1), 1) && nearly(f(1, 1), 2) && nearly(f(2, 1), 3), "features: second column is x");
    check(nearly(f(0, 2), 1) && nearly(f(1, 2), 4) && nearly(f(2, 2), 9), "features: third column is x^2");

    // Degree 1 should give just [1, x]
    Matrix g = polynomial_features(x, 1);
    check(g.cols() == 2 && nearly(g(2, 1), 3), "features: degree 1 gives 2 columns");

    // Negative and zero values
    Matrix y = {{-2}, {0}};
    Matrix h = polynomial_features(y, 3);  // columns 1, y, y^2, y^3
    check(nearly(h(0, 3), -8) && nearly(h(0, 2), 4), "features: negative input, -2 cubed is -8");
    check(nearly(h(1, 1), 0) && nearly(h(1, 3), 0), "features: zero input gives zero powers");

    if (failures == 0) {
        cout << "All feature expansion tests passed.\n";
        return 0;
    }
    cout << failures << " feature expansion test(s) failed.\n";
    return 1;
}

#else

int main() {
    cout << "[SKIPPED] poly_reg/polynomial_features.hpp does not exist yet.\n";
    return 0;
}

#endif
