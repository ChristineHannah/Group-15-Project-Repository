Name:Priscilla Kyamulabi
Role: Preprocessing & Dataset Utilities  
Date:18 October 2026  


1. Summary of Completed Deliverables
 Implemented the C++ source logic inside `src/preprocessing.cpp` corresponding to the header file `include/poly_reg/preprocessing.hpp`declared during Week 1.
Implemented dataset preparation utilities including Min-Max feature scaling, Z-score standardization, and train/test dataset splitting.
Handled edge cases such as zero variance/constant columns (preventing division-by-zero errors) and invalid train/test split ratios.
Verified compilation cleanly using CMake and validated data transformations locally.

2. Object-Oriented Class Structure and Implementation

Class Overview and Purpose
Created the `Preprocessing` class declared inside `include/poly_reg/preprocessing.hpp` and implemented inside `src/preprocessing.cpp` under the `PolyReg` namespace.
Purpose: To provide dedicated data transformation and preprocessing operations on feature matrices before feeding them into polynomial regression models. Standardizing features ensures numerical stability during matrix calculations.

Data and Memory Management
The `Preprocessing` class is designed as a utility class containing purely static member functions. It does not hold internal state or persistent data members directly. Instead, it receives existing `Matrix` objects by reference (`const Matrix& input_feature_matrix`), reads their grid values, and returns newly transformed `Matrix` instances or pairs of matrices.

Member Functions and Operations 
 `compute_min_max_scaling(const Matrix& input_feature_matrix)`: Scales each column's feature values to the range [0.0, 1.0] independently.
 `compute_z_score_standardization(const Matrix& input_feature_matrix)`: Standardizes each column's feature values to have a mean ($\mu$) of 0.0 and standard deviation ($\sigma$) of 1.0.
  `split_train_test_data(const Matrix& dataset_matrix, double training_proportion)`: Splits a dataset matrix into training and testing subsets according to a specified fraction (e.g., 0.8 for 80% train / 20% test).

Access Control, Encapsulation, and Program Integration
Access Control & Encapsulation: All member functions are declared `public` so that external modules (like main driver scripts, model trainers, and feature transformers) can invoke these utility tools directly. Algorithm details (computing mean, standard deviation, and bounding checks) are encapsulated inside `Preprocessing` function definitions, exposing only a clean public static interface.
Inheritance & Polymorphism:Because `Preprocessing` acts as a stateless functional utility suite for `Matrix` transformations, inheritance and polymorphism were not applied here to avoid unnecessary memory overhead.
Program Usage: The rest of the program creates a raw dataset `Matrix`, passes it to `Preprocessing::compute_z_score_standardization(...)` or `Preprocessing::split_train_test_data(...), and uses the returned preprocessed matrices to train the regression model.
---
Challenges faced
1. Generally working with Github and terminal gave me quite a hard time but i think i can now navigate around it.
2.  Handling edge cases where a feature column has zero variance (all values in the column are identical), which causes division by zero when normalizing ($\text{range} = 0$ or $\sigma = 0$). Solution: Added conditional checks in compute_min_max_scaling[cite: 10] and compute_z_score_standardization to set all output column values to 0.0 whenever range or standard deviation is zero. Also added validation checks to throw std::invalid_argument if matrix rows are insufficient for sample std dev ($N \le 1$) or if training proportion is invalid ($p \le 0$ or $p \ge 1$).

AI tools transparency
Tool Used: No AI tools were used to auto-generate this report. Gemini was consulted strictly to clarify C++ syntax and review class architecture guidelines.