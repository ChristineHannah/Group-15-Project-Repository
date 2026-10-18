**REPORT FOR RUBANGAKENE JOSHUA & KASULE ARNOLD - WEEK 1 & WEEK 2**

Date: 18/10/2026
Roles/Module: 
ARNOLD-Built the Foundational Matrix Data Structure
JOSHUA- Moduled Advanced Matrix Operations Needed for Regression Calculations



**Summmary of Completed Tasks**

-ARNOLD; 
Week 1: Implemented the Matrix  class in (include/poly_reg/matrix.hpp and src/matrix.cpp) and basic mathematical matrix operations(Matrix addition, scalar multiplication, Matrix-Matrix multiplication,Transpose)
Week 2: Implemented the actual C++ logic inside (ssrc/matrix.cpp) for the foundational matrix methods declared in week 1(constructors,addition, subtraction, scalar multiplication, matrix multiplication and transpose)


-JOSHUA;
 Week 1: Extended Arnold's Matrix class with Matrix Inversion Methods(Gauss-Jordan elimination) to enable Normal Equation solving later.
Also implemented determinant calculation and rank check helper functions to detect non-invertible matrices.
Week 2:Implemented advanced linear algebra solver functions (determinant(), inverse() and solving linear equation systems) directly inside (src/matrix.cpp)




**Object-Oriented Class Breakdown**

What Class did We Create?
- We Created the Matrix class inside (include/poly_reg/matrix.cpp) and implemented it in (src/matrix.cpp)

Purpose of the Matrix Class!
- To encapsulate 2D grid data safely and provide foundational linear algebra operations without relying on external libraries.

What Data does the Matrix Class Hold?
- It holds Private Data members that is;
int row_dimension, int column_dimension and a 2D standard container std::vector<std::vector<double>> grid_element_storage for secure memory management.


What Functions Operate on the Matrix Class Data?
-Public Member Functions include overloaded constructors, dimension getters  for example (get_rows(), get_cols()) and other functions include transpose(), compute_inverse()
-Constructors include Matrix(rows, cols, fill_value) and Matrix(rows, cols)


Why Some Members are Private and Others Public?
-Some data members are kept private to enforce encapsulation and prevent any external code(code outside the class) from corrupting internal grid dimensions.
-Meanwhile, the Public Data members provide a controlled safe interface in that the rest of the program interacts with matrix objects exclusively.


**CHALLENGES AND SOLUTIONS**
Challenge: -We are completely new to Machine Learning so we made a lot of online assistance.
- Confusing Mathematical formulae/methods eg. Gauss-Jordan Elimination

Solution: -Referring to the online class notes to build a basis for understanding of the Code.
-Made Deeper Research on the math concepts used in Gauss-Jordan Elimination.


**AI TOOL TRANSPARENCY**

AI Tools Used and Why?
-Claude AI was used to check syntax erros, how they could be corrected in any typed code and also to clarify mathematical formulas for example the Gauss-Elimination.




