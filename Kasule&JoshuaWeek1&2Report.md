**REPORT FOR RUBANGAKENE JOSHUA & KASULE ARNOLD - WEEK 1 & WEEK 2**

Date: 18/10/2026
Roles/Modules:
- ARNOLD: Built the foundational matrix data structure.
- JOSHUA: Implemented advanced matrix operations needed for regression calculations.



**Summary of Completed Tasks**

**ARNOLD**
- Week 1: Implemented the `Matrix` class in `include/poly_reg/matrix.hpp` and `src/matrix.cpp`, along with basic matrix operations: addition, scalar multiplication, matrix multiplication, and transpose.
- Week 2: Implemented the C++ logic in `src/matrix.cpp` for the foundational matrix methods declared in Week 1: constructors, addition, subtraction, scalar multiplication, matrix multiplication, and transpose.


**JOSHUA**
- Week 1: Extended Arnold's `Matrix` class with matrix inversion methods using Gauss-Jordan elimination to enable solving the normal equations. Also implemented determinant calculation and rank-check helper functions to detect non-invertible matrices.
- Week 2: Implemented advanced linear algebra solver functions (`determinant()`, `inverse()`, and linear-system solving) in `src/matrix.cpp`.




**Object-Oriented Class Breakdown**

What Class did We Create?
- We created the `Matrix` class in `include/poly_reg/matrix.hpp` and implemented it in `src/matrix.cpp`.

Purpose of the Matrix Class!
- It encapsulates 2D grid data safely and provides foundational linear algebra operations without relying on external libraries.

What Data does the Matrix Class Hold?
- It holds private data members: `row_dimension`, `column_dimension`, and a 2D standard container, `std::vector<std::vector<double>> grid_element_storage`, for secure memory management.


What Functions Operate on the Matrix Class Data?
- Public member functions include overloaded constructors, dimension getters such as `get_rows()` and `get_cols()`, and operations such as `transpose()` and `compute_inverse()`.
- Constructors include `Matrix(rows, cols, fill_value)` and `Matrix(rows, cols)`.


Why Some Members are Private and Others Public?
- Some data members are private to enforce encapsulation and prevent external code from corrupting the internal grid dimensions.
- Public members provide a controlled, safe interface through which the rest of the program interacts with matrix objects.


**CHALLENGES AND SOLUTIONS**
**Challenge:** We were new to machine learning and needed additional help understanding the concepts.
- Some mathematical formulas and methods, such as Gauss-Jordan elimination, were confusing.

**Solutions:**
- Referred to the online class notes to build a foundation for understanding the code.
- Researched the mathematical concepts used in Gauss-Jordan elimination in greater depth.


**AI TOOL TRANSPARENCY**

AI Tools Used and Why?
- Claude AI was used to check syntax errors in the code and explain how to correct them. It was also used to clarify mathematical formulas, such as those used in Gauss-Jordan elimination.
