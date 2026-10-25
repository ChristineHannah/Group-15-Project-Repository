# Group 15: Project Accomplishments Report (Weeks 3 & 4)
**Project:** Polynomial Regression & Machine Learning Library from Scratch (C++17)  
**Group Leader:** Christine Hannah Adong

----

## Executive Summary
During Weeks 3 and 4, Group 15 focused on architectural integration, core linear algebra implementation, dataset ingestion pipelines, data preprocessing routines, and rigorous test automation. Following Bjarne Stroustrup’s object-oriented principles, the team successfully unified individual modules into a cohesive, high-performance static library (`libpoly_reg.a`) backed by automated unit tests and end-to-end execution demos.

----

## Individual Team Member Contributions & Accomplishments

### 1. Arnold & Joshua — Core Linear Algebra & Matrix Engine
* **Responsibilities:** Designed and implemented the underlying mathematical data structures and advanced matrix operation solvers.
* **Week 3 Accomplishments:**
  * Developed the core `Matrix` class (`include/poly_reg/matrix.hpp` and `src/matrix.cpp`), supporting dynamic sizing, bounds-checked element access (`at()`), and initializer list constructors.
  * Implemented core operator overloads (`+`, `-`, `*`) for matrix arithmetic and scalar multiplication.
* **Week 4 Accomplishments:**
  * Implemented advanced linear algebra routines, including matrix transposition (`transpose()`), Gaussian elimination for determinant calculation (`compute_determinant()`), and Gauss-Jordan elimination for matrix inversion (`compute_inverse()`).
  * Authored comprehensive unit tests (`tests/test_matrix.cpp`) verifying arithmetic correctness, exception handling, and matrix inversion solvers.

### 2. Tatiana — Preprocessing, Scaling & Regression Metrics
* **Responsibilities:** Built data normalization pipelines, feature scaling modules, and model evaluation metrics.
* **Week 3 Accomplishments:**
  * Implemented feature preprocessing utilities (`include/poly_reg/preprocessing.hpp` and `src/preprocessing.cpp`), including Min-Max feature normalization and Z-score standardization.
  * Developed dataset splitting routines for training and testing data partitions.
* **Week 4 Accomplishments:**
  * Integrated evaluation metric functions directly into the model architecture (`calculate_mse` and `calculate_rmse`) to quantify model error against ground-truth targets.
  * Authored preprocessing unit tests (`tests/test_preprocessing.cpp`) validating scaling bounds and numerical stability.

### 3. Pruna — CSV Data Ingestion & Exporter Module
* **Responsibilities:** Handled robust file input/output parsing and dataset loading pipelines.
* **Week 3 Accomplishments:**
  * Developed the `CSVLoader` class (`include/poly_reg/csv_loader.hpp` and `src/csv_loader.cpp`) to parse comma-separated datasets from disk into structured `Matrix` objects.
  * Implemented robust exception handling for missing files, ragged rows, and malformed numeric entries.
* **Week 4 Accomplishments:**
  * Implemented a prediction export module (`export_predictions_to_csv`) allowing trained models to write inferred target vectors and ground truths back to `data/output/` for external analysis.
  * Verified file I/O operations through automated ingestion tests.

### 4. Allan — End-to-End Regression Pipeline & Demos
* **Responsibilities:** Implemented core Ordinary Least Squares (OLS) closed-form solvers, iterative Gradient Descent optimization, and demonstration drivers.
* **Week 3 Accomplishments:**
  * Implemented polynomial feature expansion (`include/poly_reg/feature_expansion.hpp` and `src/feature_expansion.cpp`) to transform 1D inputs into multi-degree feature matrices.
  * Developed the core `PolynomialRegression` class supporting the normal equation closed-form solver ($\beta = (X^T X)^{-1} X^T y$).
* **Week 4 Accomplishments:**
  * Implemented the iterative Gradient Descent optimization solver (`fit_gradient_descent`) with configurable learning rates ($\alpha$) and epoch iterations.
  * Created multiple project demonstration binaries (`run_demo`, `run_gd_demo`, `run_export_demo`, and `run_graph_demo`), including a terminal-based ASCII graph renderer to visually plot model curves against actual data points.

----

## Module Integration & Build Validation

* **Build System:** Configured a modern, cross-platform root `CMakeLists.txt` enforcing C++17 standards globally.
* **Test Architecture:** Separated test suites into independent executable targets (`test_matrix`, `test_preprocessing`, `test_regression`, `test_gradient_descent`) to prevent symbol collisions and ensure reliable CI/CD test execution.
* **Peer Validation:** Distributed the codebase for external peer testing, confirming zero-error compilation across independent developer environments.

-----

## 3. AI Tool Usage & Transparency
* **Tools Used:** Gemini, Claude
* **Purpose:** AI was mainly used this week for debugging, learning how to build the entire project and run the separate test and demo files. It was also used to further break down and understand the code.

----

## 4. Next Week's Objectives (Week 4)
* Next week is mainly for distributing code among peers and collecting their test results.
* Making final touches on the code, including extra examples if necessary and final debugging.
* Preparing for the presentation as a group.