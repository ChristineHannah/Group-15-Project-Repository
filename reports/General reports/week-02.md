# Week 02 Status Report - Group 15

**Project:** Polynomial Regression from Scratch in C++17 
**Date:** 18th October 2026  
**Group Leader:** Christine Hannah Adong

## 1. Executive Summary
During Week 2, the team transitioned from structural header blueprints to full C++ source implementations. All core computational modules—including Arnold and Joshua's matrix algebra solvers, Tatiana's preprocessing engine, Pruna's CSV loader, and Ibrahim's feature expansion—were merged into `main` following rigorous local CMake builds and unit test verification.

## 2. Completed Tasks & Individual Contributions
* **Christine Hannah Adong:** Managed GitHub Pull Request reviews, resolved merge integrations, updated `CMakeLists.txt` with new `.cpp` targets, and compiled this group report.
* **Kasule Arnold:** Implemented core C++ arithmetic logic.
* **Rubangakene Joshua:** Implemented advanced linear algebra solvers inside `src/matrix.cpp`.
* **Kyamulabi Tatiana:** Implemented Min-Max feature scaling, Z-score standardization, and train/test splitting inside `src/preprocessing.cpp`.
* **Anzoa Pruna:** Implemented CSV parsing logic with rigorous error checking inside `src/csv_loader.cpp`.
* **Tanga Ibrahim:** Implemented polynomial feature expansion inside `src/feature_expansion.cpp`.
* **Gidudud Allan Bright:** Verified dataset compatibility for multi-degree polynomial expansion and updated documentation.
* **Kyanka Joseph:** Updated and executed test suites in `tests/test_matrix.cpp` and `tests/test_preprocessing.cpp`, verifying 100% test passes.

## 3. AI Tool Usage & Transparency
* **Tools Used:** Gemini
* **Purpose:** Debugging Gaussian elimination matrix pivoting syntax and verifying that the code implemented was related to Bjarne Stroustrup PPP textbook.

## 4. Next Week's Objectives (Week 3)
* Integrate modules into the Ordinary Least Squares (OLS) regression training pipeline ($\beta = (X^T X)^{-1} X^T y$).
* Implement model evaluation metrics (MSE, RMSE) and runnable CLI examples.