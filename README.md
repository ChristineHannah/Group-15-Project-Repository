# Polynomial Regression from Scratch (C++)

A group project for **Machine Learning 7**. We implement polynomial regression from the ground up in C++17 and CMake, with no external machine learning libraries. Everything from CSV loading to matrix algebra to scaling is written by us.

---

## Table of Contents

1. [Project Objective](#project-objective)
2. [Prerequisites](#prerequisites)
3. [Getting Started](#getting-started)
4. [Building the Project](#building-the-project)
5. [Running Tests](#running-tests)
6. [Project Structure](#project-structure)
7. [Module Overview](#module-overview)
8. [Sample Data](#sample-data)
9. [Running the Training and Evaluation Demo](#running-the-training-and-evaluation-demo)
10. [Team Roles (Week 1)](#team-roles-week-1)
11. [Team Roles (Week 2)](#team-roles-week-2)
12. [Team Roles (Week 3)](#team-roles-week-3)
13. [Git Workflow](#git-workflow)
14. [Coding Guidelines](#coding-guidelines)

---

## Project Objective

Polynomial regression fits a curve of the form

```
y = b0 + b1·x + b2·x² + ... + bn·xⁿ
```

to a set of data points. It is solved as a linear regression problem on expanded polynomial features, using the **Normal Equation**:

```
θ = (XᵀX)⁻¹ Xᵀ y
```

To get there, we build every layer ourselves:

1. **Load** numeric data from CSV files into C++ containers.
2. **Represent** data with a custom `Matrix` class (addition, multiplication, transpose, inversion).
3. **Preprocess** data with scaling and train/test splitting.
4. **Verify** each module with automated tests.

The project runs over 4 weeks. Week 1 covers the foundation: data loading, matrices, preprocessing, tests and repository setup. Week 2 builds the regression model on top of it: feature expansion, the Normal Equation solver, evaluation metrics (MSE and RMSE), prediction export and regression tests. Week 3 connects everything into one training pipeline (raw CSV in, polynomial features, weights, predictions and scores out), adds test datasets for degrees 1 to 4, and verifies the results with integration tests.

---

## Prerequisites

| Tool | Minimum version | Purpose |
| --- | --- | --- |
| C++ compiler (GCC, Clang or MSVC) | C++17 support | Compiling the code |
| CMake | 3.10+ | Build system |
| Git | any recent version | Version control |

Check your setup:

```bash
g++ --version     # or clang++ --version
cmake --version
git --version
```

---

## Getting Started

Clone the repository and move into it:

```bash
git clone <repository-url>
cd <repository-folder>
```

---

## Building the Project

From the project root:

```bash
cmake -B build
cmake --build build
```

The first command configures the project and generates build files in `build/`. The second compiles the library and test executables.

To start fresh, delete the `build/` folder and run both commands again.

---

## Running Tests

After building, run the test executables from the `build/` folder (exact names are defined in `CMakeLists.txt`):

```bash
./build/test_matrix
./build/test_preprocessing
./build/test_regression
```

If the tests are registered with CTest, you can run them all at once:

```bash
ctest --test-dir build --output-on-failure
```

All tests should pass before a Pull Request is merged.

---

## Project Structure

```
.
├── CMakeLists.txt        # Root build configuration
├── .gitignore
├── README.md
├── include/
│   └── poly_reg/         # Public headers (.hpp)
│       ├── csv_loader.hpp
│       ├── matrix.hpp
│       ├── preprocessing.hpp
│       ├── feature_expansion.hpp
│       └── polynomial_regression.hpp
├── src/                  # Implementations (.cpp)
│   ├── csv_loader.cpp
│   ├── matrix.cpp
│   ├── preprocessing.cpp
│   ├── feature_expansion.cpp
│   └── polynomial_regression.cpp
├── tests/
│   ├── test_matrix.cpp
│   ├── test_preprocessing.cpp
│   └── test_regression.cpp
├── data/
│   ├── input/            # Sample CSV datasets (degrees 1 to 5)
│   └── output/           # Saved predictions (predictions.csv)
├── examples/
└── reports/              # Weekly group status reports (e.g. week-03.md)
```

---

## Module Overview

### CSV Loader (`csv_loader.hpp` / `csv_loader.cpp`)

Reads a `.csv` file of numbers from disk into C++ memory (e.g. `std::vector<std::vector<double>>` or `Matrix` objects). It separates numeric feature columns from the target variable and handles error cases: file not found, inconsistent row lengths and malformed data.

### Matrix (`matrix.hpp` / `matrix.cpp`)

The foundational data structure. Includes constructors, element indexing, dimension checks, matrix addition, scalar multiplication, matrix-matrix multiplication and transpose.

### Advanced Matrix Operations (extends `matrix.hpp` / `matrix.cpp`)

Matrix inversion (Gauss-Jordan elimination or LU decomposition), determinant calculation, and rank-check helpers to detect singular (non-invertible) matrices. These are needed to solve the Normal Equation.

### Preprocessing (`preprocessing.hpp` / `preprocessing.cpp`)

- **Standardization** (Z-score): rescales each feature to mean 0 and standard deviation 1.
- **Min-Max Scaling**: rescales each feature to the range \[0, 1\].
- **Train/Test Split**: divides a dataset into training and testing sets (e.g. 80% / 20%).

Scaling matters because features on very different scales (e.g. age = 25 vs. income = 50,000) make learning algorithms perform poorly.

### Feature Expansion (`feature_expansion.hpp` / `feature_expansion.cpp`)

Expands each input `x` into the degree-`d` design matrix with columns `1, x, x², ..., xᵈ`. It is connected to the training pipeline, so raw datasets are transformed automatically before reaching the OLS solver.

### Polynomial Regression (`polynomial_regression.hpp` / `polynomial_regression.cpp`)

- Builds the Normal Equations matrix `XᵀX`.
- Solves for the coefficient vector `β = (XᵀX)⁻¹ Xᵀ y` using the `Matrix` inversion and multiplication from Week 2.
- Predicts `ŷ` for new inputs.
- Computes **MSE** and **RMSE** between predicted values `ŷ` and actual values `y`.

### CSV Export (extends `csv_loader.hpp` / `csv_loader.cpp`)

Saves results back to disk. Predictions are written to `data/output/predictions.csv` with the columns `x, y_actual, y_predicted`.

### Tests (`tests/`)

- `test_matrix.cpp`: checks addition, multiplication, transpose and inversion against known mathematical results.
- `test_preprocessing.cpp`: checks CSV loading and scaling output values.
- `test_regression.cpp`: checks that the calculated weights `β` match the known ground truth for simple quadratic and cubic curves.

---

## Sample Data

Sample CSV datasets for testing polynomial regression live in `data/input/`.

Expected format: numeric values only, comma-separated, one sample per row, with the feature column(s) first and the target value last. Every row must have the same number of columns.

```csv
x,y
1.0,2.1
2.0,4.9
3.0,10.2
4.0,17.1
```

### Datasets by polynomial degree

Five datasets are provided, one per true polynomial degree `d`. Each is generated from a degree-`d` curve with a small amount of noise.

| File | True degree (d) | Use |
| --- | --- | --- |
| `data/input/poly_degree1.csv` | 1 | Straight line |
| `data/input/poly_degree2.csv` | 2 | Quadratic curve |
| `data/input/poly_degree3.csv` | 3 | Cubic curve |
| `data/input/poly_degree4.csv` | 4 | Quartic curve |
| `data/input/poly_degree5.csv` | 5 | Quintic curve |

**Week 3 test datasets (d = 1, 2, 3, 4):** four additional datasets are provided for the Week 3 full training demo. Use each file with its matching degree, and use other degrees on the same file to compare errors.

| File | True degree (d) | Use |
| --- | --- | --- |
| `data/input/week3_degree1.csv` | 1 | Straight line |
| `data/input/week3_degree2.csv` | 2 | Quadratic curve |
| `data/input/week3_degree3.csv` | 3 | Cubic curve |
| `data/input/week3_degree4.csv` | 4 | Quartic curve |

They use the same format as the files above: `x,y` columns, comma-separated, one sample per row.

Fitting with a degree **lower** than the true degree gives **underfitting** (high error on all points). Fitting with a degree **higher** than the true degree can give **overfitting**: the training error keeps dropping because the curve starts following the noise, but the model generalises worse to unseen data.

---

## Running the Training and Evaluation Demo

Build the project first (see [Building the Project](#building-the-project)). Then run the demo from the project root.

**1. Train and evaluate on a dataset** (arguments: input file, polynomial degree):

```bash
./build/poly_reg_demo data/input/poly_degree2.csv 2
```

This loads the CSV, expands `x` into a degree-2 design matrix, solves for `β` with the Normal Equation, predicts `ŷ`, prints the coefficients, MSE and RMSE, and saves the predictions to `data/output/predictions.csv`.

**2. Run every dataset with its matching degree:**

```bash
./build/poly_reg_demo data/input/poly_degree1.csv 1
./build/poly_reg_demo data/input/poly_degree2.csv 2
./build/poly_reg_demo data/input/poly_degree3.csv 3
./build/poly_reg_demo data/input/poly_degree4.csv 4
./build/poly_reg_demo data/input/poly_degree5.csv 5
```

**3. Demonstrate underfitting and overfitting:** fit the same dataset with different degrees and compare the error.

```bash
./build/poly_reg_demo data/input/poly_degree2.csv 1   # underfit: error is high
./build/poly_reg_demo data/input/poly_degree2.csv 2   # good fit: error close to the noise level
./build/poly_reg_demo data/input/poly_degree2.csv 5   # overfit: training error is lowest, but the curve follows noise
```

**4. Check the output file:**

```bash
cat data/output/predictions.csv
```

Expected format:

```csv
x,y_actual,y_predicted
1.0,2.1,2.0
2.0,4.9,5.1
```

**5. Run the regression tests:**

```bash
./build/test_regression
```

> Note: the folder `data/output/` must exist before running the demo. It is created in the repository with a placeholder file, so no extra setup is needed after cloning.

---

### Week 3: Full training demo (step by step)

This walks through the full Week 3 pipeline: load a CSV, expand `x` into polynomial features, compute `XᵀX` and `Xᵀy`, solve for `β`, predict, score (MSE and RMSE) and save the results.

**Step 0: Build** (from the project root):

```bash
cmake -B build
cmake --build build
```

**Step 1: Train on each Week 3 test dataset (`week3_degree1.csv` to `week3_degree4.csv`)** with its matching degree:

```bash
./build/poly_reg_demo data/input/week3_degree1.csv 1
./build/poly_reg_demo data/input/week3_degree2.csv 2
./build/poly_reg_demo data/input/week3_degree3.csv 3
./build/poly_reg_demo data/input/week3_degree4.csv 4
```

When the degree matches the data, the printed coefficients should be close to the curve the data was generated from, and the RMSE should be close to the noise level. Each run overwrites `data/output/predictions.csv`, so copy the file elsewhere if you want to keep a result.

**Step 2: Compare degrees on the same dataset** (for example, a degree-4 dataset fitted too low):

```bash
./build/poly_reg_demo data/input/week3_degree4.csv 2   # underfit: error is high
./build/poly_reg_demo data/input/week3_degree4.csv 4   # matching degree: error close to the noise level
```

**Step 3: Run all tests at once:**

```bash
ctest --test-dir build --output-on-failure
```

**Troubleshooting**

| Problem | Likely cause and fix |
| --- | --- |
| `./build/poly_reg_demo: No such file or directory` | The project is not built yet, or the executable has a different name. Run the build commands and check the target name in `CMakeLists.txt`. |
| File not found error | Run the demo from the project root so that `data/input/...` resolves correctly. |
| Singular matrix error | The degree is too high for the number of data points, so `XᵀX` cannot be inverted. Use a lower degree. |
| Cannot write `predictions.csv` | The `data/output/` folder is missing. Recreate it with `mkdir -p data/output`. |

---

## Team Roles (Week 1)

| Member | Role | Deliverables |
| --- | --- | --- |
| **Pruna Anzoa** | Data loading: CSV parser with error handling | `include/poly_reg/csv_loader.hpp`, `src/csv_loader.cpp` |
| **Kasule Arnold and Tanga Ibrahim** | Foundational `Matrix` class and basic operations | `include/poly_reg/matrix.hpp`, `src/matrix.cpp` |
| **Joshua (Rujo)** | Advanced matrix operations: inversion, determinant, rank check | Extensions to `matrix.hpp` and `matrix.cpp` |
| **Tatiana (Kyamulabi Priscilla)** | Preprocessing: Z-score, Min-Max scaling, train/test split | `include/poly_reg/preprocessing.hpp`, `src/preprocessing.cpp` |
| **Joseph** | Testing: test suites for all Week 1 modules | `tests/test_matrix.cpp`, `tests/test_preprocessing.cpp` |
| **Christine** | Repository setup, CMake build system, PR review and merging | `.gitignore`, `CMakeLists.txt`, folder layout, branch protection |
| **Allan** | Documentation: README, sample datasets, header comments | `README.md`, CSV files in `data/input/` |

---

## Team Roles (Week 2)

| Member | Role | Deliverables |
| --- | --- | --- |
| **Kasule Arnold** | Normal Equations matrix product `XᵀX` | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Joshua (Rujo)** | Coefficient vector `β = (XᵀX)⁻¹ Xᵀ y` using `inverse()` and matrix multiplication | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Tatiana (Kyamulabi Priscilla)** | Prediction, MSE and RMSE | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Tanga Ibrahim** | Feature expansion connected to the training pipeline (degree-`d` design matrix) | `include/poly_reg/feature_expansion.hpp`, `src/feature_expansion.cpp` |
| **Pruna Anzoa** | CSV export of predictions to `data/output/predictions.csv` | `include/poly_reg/csv_loader.hpp`, `src/csv_loader.cpp`, `data/output/` |
| **Allan** | Test datasets for d = 1 to 5, and README demo commands | `data/input/` datasets, `README.md` |
| **Joseph** | Unit and integration tests for the regression weights | `tests/test_regression.cpp` |

---

## Team Roles (Week 3)

| Member | Role | Deliverables |
| --- | --- | --- |
| **Kasule Arnold** | First half of the regression engine: transposed design matrix `Xᵀ` and the product `XᵀX` | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Joshua (Rujo)** | Inverts `XᵀX` with the Week 2 matrix inverse, multiplies by `Xᵀy` and computes the weights `β` | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Tatiana (Kyamulabi Priscilla)** | Evaluation functions: MSE and RMSE between predicted and actual values | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Tanga Ibrahim** | Connects the Week 2 polynomial feature expansion into the training pipeline so raw inputs become polynomial degrees automatically | `include/poly_reg/feature_expansion.hpp`, `src/feature_expansion.cpp` |
| **Pruna Anzoa** | Extends the CSV loader to export predictions and final evaluation scores | `include/poly_reg/csv_loader.hpp`, `src/csv_loader.cpp`, `data/output/predictions.csv` |
| **Allan** | Test datasets for d = 1, 2, 3, 4, and README instructions for running the full training demo | `data/input/` datasets, `README.md` |
| **Joseph** | Integration tests with strict `assert()` checks that the weights match known ground truths | `tests/test_regression.cpp` |
| **Christine** | Updates `CMakeLists.txt` for the regression module, reviews and merges Pull Requests, compiles the group status report, updates the README | `CMakeLists.txt`, `reports/week-03.md`, `README.md` |

---

## Git Workflow

The `main` branch is protected. Nobody pushes to it directly, and every change goes through a Pull Request that must be approved before merging. Christine reviews and merges PRs into `main`.

1. **Update your local copy**

   ```bash
   git checkout main
   git pull
   ```
2. **Create a new branch** for your work, named after your task:

   ```bash
   git checkout -b feature/<short-description>
   # e.g. feature/csv-loader, feature/matrix-class
   ```
3. **Commit** your changes with clear messages:

   ```bash
   git add <files>
   git commit -m "Add CSV loader with error handling"
   ```
4. **Push** the branch:

   ```bash
   git push -u origin feature/<short-description>
   ```
5. **Open a Pull Request** on GitHub targeting `main`.
6. **Check** that your code builds and your tests pass. Christine will review and merge once it doesn't break the build.

---

## Coding Guidelines

- Use **C++17** and keep headers in `include/poly_reg/`, implementations in `src/`.
- Every header (`.hpp`) should have a documentation header and inline comments explaining each class and function: purpose, parameters, return value and error behaviour.
- Handle errors explicitly (e.g. throw exceptions for invalid dimensions, missing files or singular matrices).
- Keep to one module per file pair so that PRs stay small and easy to review.
- Never commit build output. The `build/` folder is covered by `.gitignore`.