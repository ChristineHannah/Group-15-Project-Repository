# Matrix Module Report

## Purpose

The matrix module stores numbers in rows and columns and performs basic matrix calculations. It can be used by other parts of the polynomial regression project.

## Files

- `include/poly_reg/matrix.hpp` declares the `poly_reg::Matrix` class.
- `src/matrices.cpp` implements the class.
- `examples/matrix_demo.cpp` shows how to multiply two matrices and print the answer.

## How it works

The class stores matrix values in a one-dimensional `vector`, in row order. It keeps the number of rows and columns so it can find each value's position.

The class can create an empty matrix, create a matrix filled with zeros, or create a matrix from rows of values. It supports reading and changing values, addition, subtraction, multiplication by a number, matrix multiplication, and transpose.

The program checks that matrices have matching sizes for addition and subtraction, that the dimensions allow matrix multiplication, and that an accessed position is inside the matrix. It reports invalid input with exceptions.

The implementation and example use `namespace std` to avoid writing `std::` before standard library names. The class remains inside the `poly_reg` namespace to keep the project code organized.

## Example result

The demo multiplies a 2-by-3 matrix by a 3-by-2 matrix. It prints:

```
58 64
139 154
```

## Limitations

The module provides basic matrix operations only. It does not include matrix inversion, determinant calculation, or a general automated test suite. The example uses fixed values.
