**Progress Report - Week 3**
**Prepared by:** Joshua & Arnold

**Date:** October 24, 2026

**Role:**
- Arnold:
  - Built the first half of the regression math engine.
  - Wrote the C++ code that computes $X^T$ (the transposed design matrix) and multiplied it by $X$ ($X^TX$).

- Joshua:
  - Modified Arnold's code by taking $X^TX$, inverting it using the matrix inverse tool from Week 2, and then multiplying it by $X^T y$.
  - Calculated the final weight coefficients ($\beta$) that define the regression curve.

1. **Summary of Completed Deliverables**
*A short overview of what was accomplished in Week 3.*

- In Week 3, we handled the transposed design matrix and the weight coefficients of the polynomial curve.
- This was achieved by writing C++ code that includes the transposed design matrix and uses the matrix inverse tool developed in Week 2.

2. **Object-Oriented Class Breakdown**

**What class did we create?**
- We created the `Matrix` class in `include/poly_reg/matrix.hpp` and implemented it in `src/matrix.cpp`.
- The class is designed to encapsulate 2D grid data and provide foundational linear algebra operations without relying on external libraries.

**Purpose of the Matrix class**
- To encapsulate 2D grid data safely and provide foundational linear algebra operations without relying on external libraries.
- It manages 2D matrix data securely and exposes only the operations needed for matrix computation.

**What data does the Matrix class hold?**
- It holds private data members: `row_dimension`, `column_dimension`, and a 2D standard container, `std::vector<std::vector<double>> grid_element_storage`, for secure memory management.

**What functions operate on the Matrix class data?**
- Public member functions include overloaded constructors, dimension getters such as `get_rows()` and `get_cols()`, and operations such as `transpose()` and `compute_inverse()`.
- Constructors include `Matrix(rows, cols, fill_value)` and `Matrix(rows, cols)`.

**Why are some members private and others public?**
- Some data members are private to enforce encapsulation and prevent external code from corrupting the internal grid dimensions.
- Public members provide a controlled, safe interface through which the rest of the program interacts with matrix objects.

**Encapsulation, inheritance, and polymorphism as used in our program**

1. Encapsulation

   Here, we bundle data and the functions that operate on it into a class and hide internal details behind a public interface.

   In this project, the `Matrix` class holds its data privately and exposes only safe operations. Code such as Arnold's transpose and multiply functions, and Joshua's inverse function, cannot accidentally corrupt the internals.

2. Inheritance

   Here, a derived class reuses and extends a base class.

   In this project, polynomial regression is linear regression with a special design matrix, so it fits as a child of a general regression class.

3. Polymorphism

   The same function call behaves differently depending on the object's actual type.

   In this project, `fit()` calls `buildDesignMatrix()`, and the correct version runs automatically.

**Photo showing inheritance and polymorphism**
![alt text](<images/Joshua and Arnold.jpg>)

**Challenges and their corresponding solutions**

**Challenges**
- Not knowing whether the coefficients of the polynomial curve ($\beta$) were correct.
- Mixing up row and column indices when transposing.
- Dimension mismatches when multiplying matrices; for example, when multiplying $X^T$ by $X$, there was confusion about the order of the matrices.

**Corresponding solutions**
- Running test checks on the written code using logical sample numbers that produce valid results.
- Swapping the row and column counts for the new matrix and testing on a small non-square matrix.
- Making sure that the columns of the first matrix equal the rows of the second.

3. **AI Tool Transparency**
- **Tools used:**
  - Claude: Explaining matrix algebra, suggesting test cases, and cross-checking the coefficient ($\beta$) for correctness.
  - Gemini: Understanding the normal equation and why transpose is needed.

*End of Week 3 Report*
