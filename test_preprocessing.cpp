// tests/test_preprocessing.cpp
// Tests for Standardize, MinmaxScale and TraintestSplit with hand-worked values.
// NOTE: there is no CSV loading function in the code received so far, so CSV
// loading is not tested here. See the comment at the bottom.

#include <cmath>
#include <iostream>

#include "poly_reg/matrix.hpp"
#include "poly_reg/preprocessing.hpp"

using namespace std;
using namespace poly_reg;

static int failures = 0;

static void check(bool condition, const char* name) {
    if (condition) {
        cout << "[PASS] " << name << "\n";
    } else {
        cout << "[FAIL] " << name << "\n";
        ++failures;
    }
}

static bool nearly(double a, double b, double tol = 1e-6) {
    return fabs(a - b) < tol;
}

int main() {
    // ---- Standardize (per column, population standard deviation) ----
    // Column [1,2,3]: mean 2, std = sqrt(2/3) -> z-scores -1.224745, 0, 1.224745
    // Column [10,20,30] gives the same z-scores.
    Matrix d = {{1, 10}, {2, 20}, {3, 30}};
    Standardize(d);
    check(nearly(d(0, 0), -1.224745), "standardize: row 1, col 1");
    check(nearly(d(1, 0), 0.0), "standardize: row 2, col 1");
    check(nearly(d(2, 0), 1.224745), "standardize: row 3, col 1");
    check(nearly(d(0, 1), -1.224745), "standardize: row 1, col 2");
    check(nearly(d(2, 1), 1.224745), "standardize: row 3, col 2");
    check(nearly(d(0, 0) + d(1, 0) + d(2, 0), 0.0), "standardize: column mean is 0");

    // Constant column: std is 0, so values should be left alone (no divide by zero)
    Matrix c = {{5, 1}, {5, 2}, {5, 3}};
    Standardize(c);
    check(nearly(c(0, 0), 5.0) && nearly(c(2, 0), 5.0), "standardize: constant column unchanged");
    check(isfinite(c(1, 1)), "standardize: no NaN or infinity");

    // Empty matrix should not crash
    Matrix e;
    Standardize(e);
    check(e.rows() == 0, "standardize: empty matrix is safe");

    // ---- MinmaxScale ----
    Matrix m = {{1, 10}, {2, 20}, {3, 30}};
    MinmaxScale(m);  // default range 0 to 1
    check(nearly(m(0, 0), 0.0) && nearly(m(1, 0), 0.5) && nearly(m(2, 0), 1.0), "min-max: column 1 -> 0, 0.5, 1");
    check(nearly(m(0, 1), 0.0) && nearly(m(1, 1), 0.5) && nearly(m(2, 1), 1.0), "min-max: column 2 -> 0, 0.5, 1");

    Matrix m2 = {{1}, {2}, {3}};
    MinmaxScale(m2, -1.0, 1.0);  // custom range
    check(nearly(m2(0, 0), -1.0) && nearly(m2(1, 0), 0.0) && nearly(m2(2, 0), 1.0), "min-max: custom range -1 to 1");

    Matrix m3 = {{7}, {7}, {7}};
    MinmaxScale(m3);
    check(nearly(m3(0, 0), 0.0) && nearly(m3(2, 0), 0.0), "min-max: constant column becomes min value");

    // ---- TraintestSplit ----
    Matrix s = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
    auto parts = TraintestSplit(s);  // default ratio 0.8 -> 4 train, 1 test
    check(parts.first.rows() == 4 && parts.second.rows() == 1, "split 0.8 of 5 rows -> 4 train, 1 test");
    check(parts.first.cols() == 2 && parts.second.cols() == 2, "split keeps all columns");
    check(nearly(parts.first(0, 0), 1.0) && nearly(parts.first(3, 1), 40.0), "split: train rows are the first rows");
    check(nearly(parts.second(0, 0), 5.0) && nearly(parts.second(0, 1), 50.0), "split: test row is the last row");

    Matrix s4 = {{1}, {2}, {3}, {4}};
    auto half = TraintestSplit(s4, 0.5);
    check(half.first.rows() == 2 && half.second.rows() == 2, "split 0.5 of 4 rows -> 2 and 2");

    /* ---- CSV LOADING: no loader function exists in the code received so far ----
    When a load function exists, write a small CSV with ofstream (for example
    "1,10\n2,20\n3,30\n"), load it, and check the number of rows, columns and a few values.
    Also test that a missing file is reported as an error. */

    if (failures == 0) {
        cout << "All preprocessing tests passed.\n";
        return 0;
    }
    cout << failures << " preprocessing test(s) failed.\n";
    return 1;
}
