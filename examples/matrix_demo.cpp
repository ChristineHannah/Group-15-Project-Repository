#include "poly_reg/matrix.hpp"

#include <iostream>

using namespace std;

int main()
{
    poly_reg::Matrix left{{1, 2, 3}, {4, 5, 6}};
    poly_reg::Matrix right{{7, 8}, {9, 10}, {11, 12}};
    poly_reg::Matrix product = left * right;

    for (size_t row = 0; row < product.rows(); ++row) {
        for (size_t column = 0; column < product.cols(); ++column) {
            cout << product(row, column) << ' ';
        }
        cout << '\n';
    }
}
