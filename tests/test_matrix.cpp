// tests/test_matrix.cpp
// Tests for poly_reg::Matrix: construction, access, +, -, scalar *, matrix *,
// transpose, and invalid-input handling. Expected values are worked out by hand.

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "poly_reg/matrix.hpp"

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

static bool nearly(double a, double b, double tol = 1e-9) {
    return fabs(a - b) < tol;
}

// True if matrix m has the expected size and values.
static bool matches(const Matrix& m, const vector<vector<double>>& expected) {
    if (m.rows() != expected.size() || m.cols() != expected[0].size()) return false;
    for (size_t i = 0; i < expected.size(); ++i)
        for (size_t j = 0; j < expected[0].size(); ++j)
            if (!nearly(m(i, j), expected[i][j])) return false;
    return true;
}

int main() {
    Matrix A = {{1, 2}, {3, 4}};
    Matrix B = {{5, 6}, {7, 8}};

    // ---- Construction and access ----
    Matrix empty;
    check(empty.rows() == 0 && empty.cols() == 0, "empty matrix is 0x0");

    Matrix zeros(2, 3);
    check(zeros.rows() == 2 && zeros.cols() == 3, "Matrix(2,3) has correct size");
    check(nearly(zeros(1, 2), 0.0), "Matrix(2,3) is filled with zeros");

    check(nearly(A(0, 1), 2.0) && nearly(A(1, 0), 3.0), "list constructor stores values row by row");

    A(0, 0) = 9.0;
    check(nearly(A(0, 0), 9.0), "element can be written through operator()");
    A(0, 0) = 1.0;  // put it back for the tests below

    // ---- Addition and subtraction ----
    check(matches(A + B, {{6, 8}, {10, 12}}), "addition");
    check(matches(B - A, {{4, 4}, {4, 4}}), "subtraction");

    // ---- Scalar multiplication ----
    check(matches(A * 3.0, {{3, 6}, {9, 12}}), "scalar multiplication");

    // ---- Matrix multiplication ----
    check(matches(A * B, {{19, 22}, {43, 50}}), "multiplication (2x2 * 2x2)");

    Matrix R = {{1, 2, 3}, {4, 5, 6}};      // 2x3
    Matrix S = {{7, 8}, {9, 10}, {11, 12}}; // 3x2
    check(matches(R * S, {{58, 64}, {139, 154}}), "multiplication (2x3 * 3x2)");

    Matrix I = {{1, 0}, {0, 1}};
    check(matches(A * I, {{1, 2}, {3, 4}}), "multiplying by identity changes nothing");

    // ---- Transpose ----
    check(matches(R.transpose(), {{1, 4}, {2, 5}, {3, 6}}), "transpose of 2x3");
    check(matches(A.transpose().transpose(), {{1, 2}, {3, 4}}), "transpose twice returns original");

    // ---- Invalid inputs ----
    bool t1 = false;
    try { A(2, 0); } catch (const out_of_range&) { t1 = true; }
    check(t1, "out-of-range row throws");

    bool t2 = false;
    try { A(0, 2); } catch (const out_of_range&) { t2 = true; }
    check(t2, "out-of-range column throws");

    bool t3 = false;
    try { Matrix bad = {{1, 2}, {3}}; } catch (const invalid_argument&) { t3 = true; }
    check(t3, "rows of different lengths throw");

    bool t4 = false;
    try { A + R; } catch (const invalid_argument&) { t4 = true; }
    check(t4, "adding different sizes throws");

    bool t5 = false;
    try { A - R; } catch (const invalid_argument&) { t5 = true; }
    check(t5, "subtracting different sizes throws");

    bool t6 = false;
    try { R * R; } catch (const invalid_argument&) { t6 = true; }  // 2x3 * 2x3 is not allowed
    check(t6, "multiplying incompatible sizes throws");

    /* ---- INVERSION: not in the poly_reg::Matrix class yet ----
    Joshua's inverse() is in a different Matrix class. Once it is merged into
    poly_reg::Matrix, remove this comment and keep these tests:

    Matrix D = {{4, 7}, {2, 6}};
    check(matches(D.inverse(), {{0.6, -0.7}, {-0.2, 0.4}}), "inversion");
    check(matches(D * D.inverse(), {{1, 0}, {0, 1}}), "matrix times its inverse = identity");
    */

    if (failures == 0) {
        cout << "All matrix tests passed.\n";
        return 0;
    }
    cout << failures << " matrix test(s) failed.\n";
    return 1;
}
