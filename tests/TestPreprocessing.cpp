// tests/test_preprocessing_ch1to8.cpp
// Preprocessing tests written with the basics from chapters 1 to 8: functions,
// if statements, exceptions and classes used through their public interface.
// Same checks and expected values as test_preprocessing.cpp.

#include <iostream>
#include <string>
#include <utility>

#include "poly_reg/matrix.hpp"
#include "poly_reg/preprocessing.hpp"

using namespace std;
using namespace poly_reg;

int failures = 0;  // counts how many checks failed

// Print PASS or FAIL for one check and count failures.
void check(bool ok, string name) {
    if (ok) {
        cout << "[PASS] " << name << "\n";
    } else {
        cout << "[FAIL] " << name << "\n";
        failures = failures + 1;
    }
}

// True if a and b are equal to within 0.000001.
bool near(double a, double b) {
    double diff = a - b;
    if (diff < 0) diff = -diff;
    return diff < 0.000001;
}

int main() {
    // ---- Standardize: each column gets mean 0 and standard deviation 1 ----
    // Column 1,2,3: mean 2, standard deviation sqrt(2/3), z-scores -1.224745, 0, 1.224745
    Matrix d = {{1, 10}, {2, 20}, {3, 30}};
    Standardize(d);
    check(near(d(0, 0), -1.224745), "standardize: row 1, col 1");
    check(near(d(1, 0), 0.0), "standardize: row 2, col 1");
    check(near(d(2, 0), 1.224745), "standardize: row 3, col 1");
    check(near(d(0, 1), -1.224745), "standardize: row 1, col 2");
    check(near(d(2, 1), 1.224745), "standardize: row 3, col 2");
    check(near(d(0, 0) + d(1, 0) + d(2, 0), 0.0), "standardize: column sums to 0");

    // A column where every value is the same must be left alone (no divide by zero)
    Matrix c = {{5, 1}, {5, 2}, {5, 3}};
    Standardize(c);
    check(near(c(0, 0), 5.0) && near(c(2, 0), 5.0), "standardize: constant column unchanged");
    check(c(1, 1) >= -5.0 && c(1, 1) <= 5.0, "standardize: no NaN or infinity");

    Matrix e;  // empty matrix must not crash
    Standardize(e);
    check(e.rows() == 0, "standardize: empty matrix is safe");

    // ---- MinmaxScale: each column is scaled into a range ----
    Matrix m = {{1, 10}, {2, 20}, {3, 30}};
    MinmaxScale(m);  // default range 0 to 1
    check(near(m(0, 0), 0.0) && near(m(1, 0), 0.5) && near(m(2, 0), 1.0), "min-max: column 1 gives 0, 0.5, 1");
    check(near(m(0, 1), 0.0) && near(m(1, 1), 0.5) && near(m(2, 1), 1.0), "min-max: column 2 gives 0, 0.5, 1");

    Matrix m2 = {{1}, {2}, {3}};
    MinmaxScale(m2, -1.0, 1.0);
    check(near(m2(0, 0), -1.0) && near(m2(1, 0), 0.0) && near(m2(2, 0), 1.0), "min-max: range -1 to 1");

    Matrix m3 = {{7}, {7}, {7}};
    MinmaxScale(m3);
    check(near(m3(0, 0), 0.0) && near(m3(2, 0), 0.0), "min-max: constant column becomes the minimum");

    // ---- TraintestSplit: first rows are training data, last rows are test data ----
    Matrix s = {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
    pair<Matrix, Matrix> parts = TraintestSplit(s);  // default ratio 0.8
    check(parts.first.rows() == 4 && parts.second.rows() == 1, "split 0.8 of 5 rows gives 4 train, 1 test");
    check(parts.first.cols() == 2 && parts.second.cols() == 2, "split keeps all columns");
    check(near(parts.first(0, 0), 1.0) && near(parts.first(3, 1), 40.0), "split: train rows are the first rows");
    check(near(parts.second(0, 0), 5.0) && near(parts.second(0, 1), 50.0), "split: test row is the last row");

    Matrix s4 = {{1}, {2}, {3}, {4}};
    pair<Matrix, Matrix> half = TraintestSplit(s4, 0.5);
    check(half.first.rows() == 2 && half.second.rows() == 2, "split 0.5 of 4 rows gives 2 and 2");

    if (failures == 0) {
        cout << "All preprocessing tests passed.\n";
        return 0;
    }
    cout << failures << " preprocessing test(s) failed.\n";
    return 1;
}
