// tests/test_csv_loader.cpp
// Tests for the CSV loader.
//
// ASSUMED interface (change the ADJUST lines to match the real code):
//   header:   poly_reg/csv_loader.hpp
//   function: Matrix load_csv(const std::string& path);   // throws if the file cannot be opened
//
// If the header does not exist yet, this test compiles, prints SKIPPED and
// exits with 0, so it cannot break the build. It switches on by itself once
// the header is added.

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "poly_reg/matrix.hpp"

using namespace std;
using namespace poly_reg;

#if defined(__has_include)
#if __has_include("poly_reg/csv_loader.hpp")  // ADJUST: real header name
#define HAS_CSV_LOADER 1
#endif
#endif

#ifdef HAS_CSV_LOADER

#include "poly_reg/csv_loader.hpp"  // ADJUST: real header name

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
    // Write a small CSV with known numbers (no header row).
    const string path = "test_data.csv";
    {
        ofstream out(path);
        out << "1,10\n2,20\n3,30\n";
    }

    Matrix data = load_csv(path);  // ADJUST: function name and return type

    check(data.rows() == 3, "csv: loads 3 rows");
    check(data.cols() == 2, "csv: loads 2 columns");
    check(nearly(data(0, 0), 1) && nearly(data(0, 1), 10), "csv: first row is 1,10");
    check(nearly(data(2, 0), 3) && nearly(data(2, 1), 30), "csv: last row is 3,30");

    // Decimals and negative numbers
    {
        ofstream out(path);
        out << "-1.5,0.25\n2.75,-4\n";
    }
    Matrix d2 = load_csv(path);
    check(nearly(d2(0, 0), -1.5) && nearly(d2(0, 1), 0.25), "csv: reads negative and decimal values");
    check(nearly(d2(1, 0), 2.75) && nearly(d2(1, 1), -4.0), "csv: reads second row of decimals");

    // Invalid input: missing file must be reported as an error
    bool threw = false;
    try { load_csv("this_file_does_not_exist.csv"); } catch (...) { threw = true; }
    check(threw, "csv: missing file throws");  // ADJUST if the loader returns an empty Matrix instead

    remove(path.c_str());

    if (failures == 0) {
        cout << "All CSV loader tests passed.\n";
        return 0;
    }
    cout << failures << " CSV loader test(s) failed.\n";
    return 1;
}

#else

int main() {
    cout << "[SKIPPED] poly_reg/csv_loader.hpp does not exist yet.\n";
    return 0;
}

#endif
