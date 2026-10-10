// tests/test_matrix_inverse.cpp
// Tests for determinant() and inverse() on poly_reg::Matrix.
//
// These functions are not in poly_reg::Matrix yet (Joshua's version is in a
// separate class). Until they are added, this test compiles, prints SKIPPED
// and exits with 0, so it cannot break the build.
//
// WHEN JOSHUA'S CODE IS MERGED: change the 0 below to 1, then rebuild and run.
#define MATRIX_HAS_INVERSE 0

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "poly_reg/matrix.hpp"

using namespace std;
using namespace poly_reg;

#if MATRIX_HAS_INVERSE

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
    return fabs(a - b) < tol;
}

static bool matches(const Matrix& m, const vector<vector<double>>& expected) {
    if (m.rows() != expected.size() || m.cols() != expected[0].size()) return false;
    for (size_t i = 0; i < expected.size(); ++i)
        for (size_t j = 0; j < expected[0].size(); ++j)
            if (!nearly(m(i, j), expected[i][j])) return false;
    return true;
}

int main() {
    // ---- Determinant ----
    Matrix D = {{4, 7}, {2, 6}};                 // 4*6 - 7*2 = 10
    check(nearly(D.determinant(), 10.0), "determinant of [[4,7],[2,6]] = 10");

    Matrix E = {{1, 2}, {3, 4}};                 // 1*4 - 2*3 = -2
    check(nearly(E.determinant(), -2.0), "determinant of [[1,2],[3,4]] = -2");

    Matrix S = {{1, 2}, {2, 4}};                 // second row = 2 * first row
    check(nearly(S.determinant(), 0.0), "determinant of a singular matrix = 0");

    Matrix T = {{2, 0, 0}, {0, 3, 0}, {0, 0, 4}};  // diagonal: 2*3*4
    check(nearly(T.determinant(), 24.0), "determinant of 3x3 diagonal = 24");

    // ---- Inverse ----
    check(matches(D.inverse(), {{0.6, -0.7}, {-0.2, 0.4}}), "inverse of [[4,7],[2,6]]");
    check(matches(T.inverse(), {{0.5, 0, 0}, {0, 1.0 / 3.0, 0}, {0, 0, 0.25}}), "inverse of 3x3 diagonal");
    check(matches(D * D.inverse(), {{1, 0}, {0, 1}}), "matrix times its inverse = identity");

    // ---- Invalid inputs ----
    bool t1 = false;
    try { S.inverse(); } catch (const exception&) { t1 = true; }
    check(t1, "inverse of a singular matrix throws");

    Matrix R = {{1, 2, 3}, {4, 5, 6}};
    bool t2 = false;
    try { R.determinant(); } catch (const exception&) { t2 = true; }
    check(t2, "determinant of a non-square matrix throws");

    bool t3 = false;
    try { R.inverse(); } catch (const exception&) { t3 = true; }
    check(t3, "inverse of a non-square matrix throws");

    if (failures == 0) {
        cout << "All inverse/determinant tests passed.\n";
        return 0;
    }
    cout << failures << " inverse/determinant test(s) failed.\n";
    return 1;
}

#else

int main() {
    cout << "[SKIPPED] determinant()/inverse() are not in poly_reg::Matrix yet.\n";
    return 0;
}

#endif
