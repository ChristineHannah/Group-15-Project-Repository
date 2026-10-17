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
9. [Team Roles (Week 1)](#team-roles-week-1)
10. [Git Workflow](#git-workflow)
11. [Coding Guidelines](#coding-guidelines)

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

The project runs over 4 weeks. Week 1 covers the foundation: data loading, matrices, preprocessing, tests and repository setup. Later weeks build the regression model on top of it.

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
│       └── preprocessing.hpp
├── src/                  # Implementations (.cpp)
│   ├── csv_loader.cpp
│   ├── matrix.cpp
│   └── preprocessing.cpp
├── tests/
│   ├── test_matrix.cpp
│   └── test_preprocessing.cpp
├── data/
│   └── input/            # Sample CSV datasets
├── examples/
└── reports/
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

### Tests (`tests/`)

- `test_matrix.cpp`: checks addition, multiplication, transpose and inversion against known mathematical results.
- `test_preprocessing.cpp`: checks CSV loading and scaling output values.

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