WEEK THREE

Name: Kyamulabi Priscilla  
Role: Regression Evaluation Metrics & Model Testing  
Date: 23 October 2026  

1. Summary of Completed Deliverables
* Implemented the C++ evaluation metrics logic inside `src/polynomial_regression.cpp` corresponding to model performance testing.
* Developed regression evaluation functions including Mean Squared Error (`compute_mean_squared_error`) and Root Mean Squared Error (`compute_root_mean_squared_error`) by comparing predicted values against actual ground truth targets.
* Implemented robust error handling to validate dimension matching between true and predicted matrices and prevent empty matrix computations.
* Verified compilation cleanly using the project's CMake build configuration.

2. Object-Oriented Class Structure and Implementation

Class Overview and Purpose
Implemented the `RegressionMetrics` class (or utility structure) under the `PolyReg` namespace within `include/poly_reg/polynomial_regression.hpp` and `src/polynomial_regression.cpp`.
Purpose: To provide rigorous quantitative evaluation tools that test how well the polynomial regression model performed by calculating prediction error against actual observed targets.

Data and Memory Management
Designed as a stateless utility class utilizing static member functions. It does not store persistent instance data members; instead, it receives true target (`y_true`) and predicted (`y_pred`) `Matrix` objects by reference (`const Matrix&`) to perform calculations safely without memory overhead.

Member Functions and Operations 
  * `compute_mean_squared_error(const Matrix& y_true, const Matrix& y_pred)`: Iterates through observations, computes squared residual differences between actual and predicted values, accumulates the total, and returns the average mean squared error.
  * `compute_root_mean_squared_error(const Matrix& y_true, const Matrix& y_pred)`: Reuses the computed MSE value and applies `std::sqrt()` to return the root mean squared error in the original units.

Access Control, Encapsulation, and Program Integration
1. Access Control & Encapsulation: All evaluation functions are declared `public` to provide an accessible interface for testing scripts and validation pipelines. The internal summation, residual calculation, and exception handling are fully encapsulated within the function scopes.
2. Inheritance & Polymorphism: Utilizes a focused functional utility structure tailored for matrix-based metric evaluations.
Program Usage: The rest of the program passes trained model predictions and actual validation datasets into `RegressionMetrics::compute_mean_squared_error` and `compute_root_mean_squared_error` to evaluate prediction accuracy.

Challenge: Potential runtime errors caused by dimension mismatches between true target matrices and predicted target matrices, or attempts to calculate metrics on empty datasets.
Solution: Added explicit validation checks at the start of compute_mean_squared_error to verify that row and column dimensions match and that the observation count is greater than zero, throwing std::invalid_argument exceptions when anomalies are detected.

AI Tool Transparency
Tool Used: No AI tools were used to auto-generate this report. Gemini was consulted strictly to clarify C++ syntax and review evaluation metric formulas.

Below is the hand drawn illustration;
![class illustration](<KyamulabiPriscilla_class_layout.jpeg>)

