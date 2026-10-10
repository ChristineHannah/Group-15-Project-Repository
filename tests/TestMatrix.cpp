// tests/test_matrix_ch1to8.cpp
// Matrix tests written with the basics from chapters 1 to 8: functions,
// vectors, if statements, exceptions (try/catch) and classes used through
// their public interface. Same checks and expected values as test_matrix.cpp.

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "poly_reg/matrix.hpp"

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

// Absolute value of a double.
double absolute(double x) {
    if (x < 0) return -x;
    return x;
}

// True if m has r rows, c columns and the given values (listed row by row).
bool same(const Matrix& m, int r, int c, const vector<double>& values) {
    if (int(m.rows()) != r || int(m.cols()) != c) return false;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (absolute(m(i, j) - values[i * c + j]) > 0.000000001) return false;
        }
    }
    return true;
}

int main() {
    Matrix A = {{1, 2}, {3, 4}};
    Matrix B = {{5, 6}, {7, 8}};
    Matrix R = {{1, 2, 3}, {4, 5, 6}};       // 2 x 3
    Matrix S = {{7, 8}, {9, 10}, {11, 12}};  // 3 x 2

    // ---- Construction and access ----
    Matrix empty;
    check(empty.rows() == 0 && empty.cols() == 0, "empty matrix is 0x0");

    Matrix zeros(2, 3);
    check(zeros.rows() == 2 && zeros.cols() == 3, "Matrix(2,3) has correct size");
    check(zeros(1, 2) == 0.0, "Matrix(2,3) is filled with zeros");

    check(A(0, 1) == 2.0 && A(1, 0) == 3.0, "list constructor stores values row by row");

    A(0, 0) = 9.0;
    check(A(0, 0) == 9.0, "element can be written");
    A(0, 0) = 1.0;  // put it back

    // ---- Arithmetic ----
    check(same(A + B, 2, 2, {6, 8, 10, 12}), "addition");
    check(same(B - A, 2, 2, {4, 4, 4, 4}), "subtraction");
    check(same(A * 3.0, 2, 2, {3, 6, 9, 12}), "scalar multiplication");
    check(same(A * B, 2, 2, {19, 22, 43, 50}), "multiplication 2x2 * 2x2");
    check(same(R * S, 2, 2, {58, 64, 139, 154}), "multiplication 2x3 * 3x2");

    // ---- Transpose ----
    check(same(R.transpose(), 3, 2, {1, 4, 2, 5, 3, 6}), "transpose of 2x3");
    check(same(A.transpose().transpose(), 2, 2, {1, 2, 3, 4}), "transpose twice returns original");

    // ---- Errors: each of these must throw an exception ----
    bool caught = false;

    try {
        A(2, 0);
    } catch (out_of_range& e) {
        caught = true;
    }
    check(caught, "row out of range throws");

    caught = false;
    try {
        A(0, 2);
    } catch (out_of_range& e) {
        caught = true;
    }
    check(caught, "column out of range throws");

    caught = false;
    try {
        Matrix bad = {{1, 2}, {3}};
    } catch (invalid_argument& e) {
        caught = true;
    }
    check(caught, "rows of different lengths throw");

    caught = false;
    try {
        Matrix wrong = A + R;
    } catch (invalid_argument& e) {
        caught = true;
    }
    check(caught, "adding different sizes throws");

    caught = false;
    try {
        Matrix wrong = A - R;
    } catch (invalid_argument& e) {
        caught = true;
    }
    check(caught, "subtracting different sizes throws");

    caught = false;
    try {
        Matrix wrong = R * R;
    } catch (invalid_argument& e) {
        caught = true;
    }
    check(caught, "multiplying incompatible sizes throws");

    if (failures == 0) {
        cout << "All matrix tests passed.\n";
        return 0;
    }
    cout << failures << " matrix test(s) failed.\n";
    return 1;
}
