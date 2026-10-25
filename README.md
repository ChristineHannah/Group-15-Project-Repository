# Polynomial Regression from Scratch (C++)

A group project for **Machine Learning 7**. We implement polynomial regression from the ground up in C++17 and CMake, with no external machine learning libraries. Everything from CSV loading to matrix algebra to scaling to model training is written by us. The model can be trained with two solvers: the closed-form **Normal Equation (OLS)** and iterative **Gradient Descent**.

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
9. [Example Use Cases](#example-use-cases)
10. [Running the Training and Evaluation Demo](#running-the-training-and-evaluation-demo)
11. [Running the Gradient Descent Demo](#running-the-gradient-descent-demo)
12. [Team Roles (Week 1)](#team-roles-week-1)
13. [Team Roles (Week 2)](#team-roles-week-2)
14. [Team Roles (Week 3)](#team-roles-week-3)
15. [Team Roles (Week 4)](#team-roles-week-4)
16. [Git Workflow](#git-workflow)
17. [Coding Guidelines](#coding-guidelines)

---

## Project Objective

Polynomial regression fits a curve of the form

```
y = b0 + b1·x + b2·x² + ... + bn·xⁿ
```

to a set of data points. It is solved as a linear regression problem on expanded polynomial features. We provide two solvers.

**1. Normal Equation (Ordinary Least Squares)**, a closed-form solution:

```
θ = (XᵀX)⁻¹ Xᵀ y
```

**2. Gradient Descent**, an iterative solution that repeatedly nudges the weights downhill on the error surface:

```
cost(θ)  = (1 / 2m) · Σ (Xθ − y)²
gradient = (1 / m) · Xᵀ (Xθ − y)
θ        = θ − α · gradient          (α = learning rate)
```

To get there, we build every layer ourselves:

1. **Load** numeric data from CSV files into C++ containers.
2. **Represent** data with a custom `Matrix` class (addition, multiplication, transpose, inversion).
3. **Preprocess** data with scaling and train/test splitting.
4. **Train** the model with two solvers (Normal Equation and Gradient Descent) and track the loss while Gradient Descent runs.
5. **Verify** each module with automated tests.

The project runs over 4 weeks. Week 1 covers the foundation: data loading, matrices, preprocessing, tests and repository setup. Week 2 builds the regression model on top of it: feature expansion, the Normal Equation solver, evaluation metrics (MSE and RMSE), prediction export and regression tests. Week 3 connects everything into one training pipeline (raw CSV in, polynomial features, weights, predictions and scores out), adds test datasets for degrees 1 to 4, and verifies the results with integration tests. Week 4 adds the second solver: Gradient Descent (cost function, gradient vector, training loop and loss tracking), optimizes feature expansion for iterative batch training, improves file routing for inputs and outputs, and finishes the final build targets, documentation and group report.

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

The first command configures the project and generates build files in `build/`. The second compiles all targets: the library, the test executables and the demo.

To start fresh, delete the `build/` folder and run both commands again.

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
│   ├── test_regression.cpp
│   └── test_gradient_descent.cpp
├── data/
│   ├── input/            # Sample CSV datasets (degrees 1 to 5)
│   └── output/           # Saved predictions (predictions.csv)
├── examples/
└── reports/
    ├── General reports
    └── Individual reports 
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

Expands each input `x` into the degree-`d` design matrix with columns `1, x, x², ..., xᵈ`. It is connected to the training pipeline, so raw datasets are transformed automatically before reaching either solver. It is optimized so that the expanded design matrix is built once and scales efficiently when it is reused over many Gradient Descent epochs.

### Polynomial Regression (`polynomial_regression.hpp` / `polynomial_regression.cpp`)

- Builds the Normal Equations matrix `XᵀX`.
- Solves for the coefficient vector `β = (XᵀX)⁻¹ Xᵀ y` using the `Matrix` inversion and multiplication from Week 2.
- Predicts `ŷ` for new inputs.
- Computes **MSE** and **RMSE** between predicted values `ŷ` and actual values `y`.

### Gradient Descent (extends `polynomial_regression.hpp` / `polynomial_regression.cpp`)

An iterative alternative to the Normal Equation that does not need a matrix inverse.

- **Cost function**: computes the mean squared error of the current weights, `J(θ) = (1 / 2m) · Σ (Xθ − y)²`.
- **Gradient vector**: computes the slope of the cost with respect to each weight, `(1 / m) · Xᵀ (Xθ − y)`, which tells the model which direction to adjust.
- **Training loop**: starting from initial weights, repeatedly steps against the gradient, scaled by the **learning rate** `α`, for a set number of epochs (or until the cost stops improving), then returns the final weights.
- **Loss tracking**: records the cost at every epoch so you can confirm the error shrinks and the model converges.

Gradient Descent is sensitive to the learning rate and to feature scale. A rate that is too large makes the cost grow or become `nan`; one that is too small converges very slowly. Scaling the features first (see Preprocessing) helps, especially for higher degrees.

### CSV Export (extends `csv_loader.hpp` / `csv_loader.cpp`)

Handles file input and output for the program: input files are read from `data/input/` and prediction results are exported to `data/output/`. Predictions are written to `data/output/predictions.csv` with the columns `x, y_actual, y_predicted`.

### Tests (`tests/`)

- `test_matrix.cpp`: checks addition, multiplication, transpose and inversion against known mathematical results.
- `test_preprocessing.cpp`: checks CSV loading and scaling output values.
- `test_regression.cpp`: checks that the calculated weights `β` match the known ground truth for simple quadratic and cubic curves.
- `test_gradient_descent.cpp`: checks the cost and gradient calculations, and that Gradient Descent converges to weights close to the Normal Equation solution.

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

## Example Use Cases

This library is a **prediction** tool: it learns a polynomial curve from example data, then uses the curve to predict `y` for an input `x`. The examples below use the small dataset from [Sample Data](#sample-data). Save it as `data/input/example.csv`:

```csv
x,y
1.0,2.1
2.0,4.9
3.0,10.2
4.0,17.1
```

The numbers below were calculated with the Normal Equation and rounded. Your demo should print the same values (to rounding), though the layout of the printout may differ.

### Use case 1: Fit a curve and predict new values

Train a degree-2 model:

```bash
./build/poly_reg_demo data/input/example.csv 2 ols
```

The learned weights give the prediction formula:

```
ŷ = 1.125 − 0.095·x + 1.025·x²        (RMSE ≈ 0.10)
```

| x | y (actual) | ŷ (predicted) |
| --- | --- | --- |
| 1.0 | 2.1 | 2.055 |
| 2.0 | 4.9 | 5.035 |
| 3.0 | 10.2 | 10.065 |
| 4.0 | 17.1 | 17.145 |

The same formula predicts values the model has not seen: **x = 5 gives ŷ ≈ 26.28** and **x = 6 gives ŷ ≈ 37.46**. The predictions for the training rows are saved to `data/output/predictions.csv` as `x, y_actual, y_predicted`.

### Use case 2: Choose the right polynomial degree

The same dataset fitted with different degrees shows underfitting and overfitting:

| Degree | RMSE | Prediction at x = 5 | What happens |
| --- | --- | --- | --- |
| 1 | ≈ 1.03 | 21.15 | **Underfit**: a straight line cannot follow the curve |
| 2 | ≈ 0.10 | 26.28 | **Good fit**: error close to the noise level |
| 3 | ≈ 0.00 | 24.70 | **Overfit**: passes through every point (4 weights for 4 points), so it follows the noise and its prediction for new data is less trustworthy |

```bash
./build/poly_reg_demo data/input/example.csv 1 ols
./build/poly_reg_demo data/input/example.csv 2 ols
./build/poly_reg_demo data/input/example.csv 3 ols
```

A lower training error does not always mean a better model. The degree-3 model has the lowest error here but is the one that overfits.

### Use case 3: Solve the same problem with Gradient Descent

Train the same degree-2 model with the iterative solver:

```bash
./build/poly_reg_demo data/input/example.csv 2 gd 0.01 5000
```

The printed loss should shrink from epoch to epoch, and the final weights and RMSE should move toward the Normal Equation result from Use case 1 as training converges. This shows both solvers reaching the same answer by different routes: one in a single step, the other by repeated small steps downhill.

For larger datasets, use the ready-made files in `data/input/` (`poly_degree1.csv` to `poly_degree5.csv`, and `week3_degree1.csv` to `week3_degree4.csv`) in the same way.

---


### Full training demo (step by step)

This walks through the full Week 3 pipeline: load a CSV, expand `x` into polynomial features, compute `XᵀX` and `Xᵀy`, solve for `β`, predict, score (MSE and RMSE) and save the results.

**Step 0: Build** (from the project root):

```bash
cmake -B build_new
cmake --build build_new
```
**Step 1 : Running all unit and integration tests**

* 1. Matrix Mathematics & Advanced Linear Algebra Solvers:

.\build_new\test_matrix.exe

* 2. Data Preprocessing & CSV Ingestion: 

.\build_new\test_preprocessing.exe

* 3. Ordinary Least Squares (OLS) Regression Integration:

.\build_new\test_regression.exe

* 4. Gradient Descent Convergence Verification:

.\build_new\test_gradient_descent.exe

**Step 2: Running all demo programs**

* Demo 1: End-to-End Ordinary Least Squares (OLS) Demo:

.\build_new\run_demo.exe

* Demo 2: Iterative Gradient Descent Optimizer Demo:

.\build_new\run_gd_demo.exe

* Demo 3: Feature Preprocessing & CSV Export Demo:

.\build_new\run_export_demo.exe

* Demo 4: Visual ASCII Terminal Graph Estimation Demo:

.\build_new\run_graph_demo.exe

**Step 3: Train on a dataset**
* To train on a specific dataset, update the dataset file path string inside your target demo file (e.g., std::string dataset_path = "data/input/cubic_noisy.csv";) and re-run:

cmake --build build_new
.\build_new\run_demo.exe


**Step 4: Compare polynomial degrees on the same dataset** 

Open examples/polynomial_regression_demo.cpp.

Change the int degree = 2; variable to different values (e.g., 1 for linear, 3 for cubic, or 5 for high-degree polynomial).

Recompile and execute:
cmake --build build_new
.\build_new\run_demo.exe

**Step 5: Comparing the two solvers (OLS vs. GRADIENT DESCENT)**
* Our library implements two distinct numerical approaches to solving polynomial regression:

**Ordinary Least Squares (OLS)**: 
Closed-form matrix inversion solver ($\beta = (X^T X)^{-1} X^T y$). Solves weights instantly in a single analytical step.
**Gradient Descent (GD)**: 
Iterative optimization solver. Updates weights step-by-step using a learning rate ($\alpha$) across multiple epochs ($\nabla J(\beta)$).

* How to Compare:Run the closed-form solver demo: 
.\build_new\run_demo.exe

* Run the iterative optimizer demo: 
.\build_new\run_gd_demo.exe

* Compare the resulting weight vectors ($\beta$) and execution times. Both solvers should converge to virtually identical parameter values for clean quadratic data.

**Step 6: Checking Model Convergence (Gradient Descent)** 
To verify that Gradient Descent successfully minimizes loss without diverging:
Run;
.\build_new\run_gradient_descent.exe or .\build_new\run_gd_demo.exe.
Inspect the Final Convergence MSE printed in the console output. A decreasing loss across epochs confirms proper hyperparameter tuning (e.g., learning rate $\alpha = 0.01$).

**Step 7: Checking the output files & CSV export**
The CSV export module allows trained models to persist predictions back to disk.

Run the export demonstration:

PowerShell
.\build_new\run_export_demo.exe

Navigate to the data/output/ directory.

Open predictions_demo.csv in any text editor or spreadsheet viewer.

Verify that it contains two comma-separated columns (y_true,y_pred), contrasting actual target values against model estimates.

**Troubleshooting**

| Problem | Likely cause and fix |
| --- | --- |
| `./build/poly_reg_demo: No such file or directory` | The project is not built yet, or the executable has a different name. Run the build commands and check the target name in `CMakeLists.txt`. |
| File not found error | Run the demo from the project root so that `data/input/...` resolves correctly. |
| Singular matrix error | The degree is too high for the number of data points, so `XᵀX` cannot be inverted. Use a lower degree. |
| Cannot write `predictions.csv` | The `data/output/` folder is missing. Recreate it with `mkdir -p data/output`. |


---
## Machine Learning Prediction Use Cases & Examples

Our C++17 Polynomial Regression library supports end-to-end machine learning workflows, including closed-form Ordinary Least Squares (OLS) training, iterative Gradient Descent optimization, feature scaling, and visual estimations.

### Use Case 1: Training an OLS Polynomial Model & Making Predictions
The following example demonstrates loading a quadratic dataset, fitting a degree-2 polynomial model, solving for the weight vector ($\beta$), and predicting outputs:

```cpp
#include <iostream>
#include "poly_reg/csv_loader.hpp"
#include "poly_reg/polynomial_regression.hpp"

int main() {
    // 1. Load dataset
    PolyReg::Matrix dataset = PolyReg::CSVLoader::load_dataset_from_csv("data/input/quadratic_clean.csv");
    
    int rows = dataset.get_rows();
    PolyReg::Matrix X(rows, 1), y(rows, 1);
    for(int i = 0; i < rows; ++i) {
        X.at(i, 0) = dataset.at(i, 0);
        y.at(i, 0) = dataset.at(i, 1);
    }

    // 2. Train Degree-2 Polynomial Regression Model
    PolyReg::PolynomialRegression model(2);
    model.fit(X, y);

    // 3. Make Predictions on New Inputs
    PolyReg::Matrix predictions = model.predict(X);
    double mse = model.calculate_mse(y, predictions);
    
    std::cout << "Model successfully trained! MSE: " << mse << "\n";
    return 0;
}
```
### Visual Model Estimation Graph
Below is a snapshot of our terminal-based ASCII visualization demo (`run_graph_demo.exe`), plotting the actual dataset points (`*`) against the model's fitted polynomial curve (`+`):

```text
--- VISUAL ESTIMATION GRAPH (* = Actual Data, + = Model Curve) ---
Y-Max (409.4)
  |                                                 *|
  |                                                + |
  |                                               *  |
  |                                              *   |
  |                                            *+    |
  |                                           *      |
  |                                         *+       |
  |                                        *+        |
  |                                      *+          |
  |                                     *+           |
  |                                    *+            |
  |                                   *+             |
  |                                  *+              |
  |                                 *+               |
  |                               **+                |
  |                             *+                   |
  |                           +*                     |
  |   +*+                   *++                      |
  |  *+*+                 *++++                      |
  |*++*+++*++*++*++*++*++*+                          |
  ----------------------------------------------------
Y-Min (3.5)                                     X-Max (15.0)

----
```

## Team Roles (Week 1)

| Member | Role | Deliverables |
| --- | --- | --- |
| **Anzoa Pruna** | Data loading: CSV parser with error handling | `include/poly_reg/csv_loader.hpp`, `src/csv_loader.cpp` |
| **Kasule Arnold and Tanga Ibrahim** | Foundational `Matrix` class and basic operations | `include/poly_reg/matrix.hpp`, `src/matrix.cpp` |
| **Rubangakene Joshua** | Advanced matrix operations: inversion, determinant, rank check | Extensions to `matrix.hpp` and `matrix.cpp` |
| **Kyamulabi Priscilla** | Preprocessing: Z-score, Min-Max scaling, train/test split | `include/poly_reg/preprocessing.hpp`, `src/preprocessing.cpp` |
| **Kyankya Joseph** | Testing: test suites for all Week 1 modules | `tests/test_matrix.cpp`, `tests/test_preprocessing.cpp` |
| **Christine Hannah Adong** | Repository setup, CMake build system, PR review and merging | `.gitignore`, `CMakeLists.txt`, folder layout, branch protection |
| **Gidudu Allan Bright** | Documentation: README, sample datasets, header comments | `README.md`, CSV files in `data/input/` |

---

## Team Roles (Week 2)

| Member | Role | Deliverables |
| --- | --- | --- |
| **Kasule Arnold** | Normal Equations matrix product `XᵀX` | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Rubangakene Joshua** | Coefficient vector `β = (XᵀX)⁻¹ Xᵀ y` using `inverse()` and matrix multiplication | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Kyamulabi Priscilla** | Prediction, MSE and RMSE | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Tanga Ibrahim** | Feature expansion connected to the training pipeline (degree-`d` design matrix) | `include/poly_reg/feature_expansion.hpp`, `src/feature_expansion.cpp` |
| **Anzoa Pruna** | CSV export of predictions to `data/output/predictions.csv` | `include/poly_reg/csv_loader.hpp`, `src/csv_loader.cpp`, `data/output/` |
| **Gidudu Allan** | Test datasets for d = 1 to 5, and README demo commands | `data/input/` datasets, `README.md` |
| **Kyankya Joseph** | Unit and integration tests for the regression weights | `tests/test_regression.cpp` |
| **Christine Hannah Adong** | Updates `CMakeLists.txt` to include the new regression module, reviews and merges everyone's Pull Requests, compiles the group status report | `CMakeLists.txt`, `reports/week-02.md` |

---

## Team Roles (Week 3)

| Member | Role | Deliverables |
| --- | --- | --- |
| **Kasule Arnold** | First half of the regression engine: transposed design matrix `Xᵀ` and the product `XᵀX` | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Rubangakene Joshua** | Inverts `XᵀX` with the Week 2 matrix inverse, multiplies by `Xᵀy` and computes the weights `β` | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Kyamulabi Priscilla** | Evaluation functions: MSE and RMSE between predicted and actual values | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Tanga Ibrahim** | Connects the Week 2 polynomial feature expansion into the training pipeline so raw inputs become polynomial degrees automatically | `include/poly_reg/feature_expansion.hpp`, `src/feature_expansion.cpp` |
| **Anzoa Pruna** | Extends the CSV loader to export predictions and final evaluation scores | `include/poly_reg/csv_loader.hpp`, `src/csv_loader.cpp`, `data/output/predictions.csv` |
| **Gidudu Allan Bright** | Test datasets for d = 1, 2, 3, 4, and README instructions for running the full training demo | `data/input/` datasets, `README.md` |
| **Kyankya Joseph** | Integration tests with strict `assert()` checks that the weights match known ground truths | `tests/test_regression.cpp` |
| **Christine Hannah Adong** | Updates `CMakeLists.txt` for the regression module, reviews and merges Pull Requests, compiles the group status report, updates the README | `CMakeLists.txt`, `reports/week-03.md`, `README.md` |

---

## Team Roles (Week 4)

| Member | Role | Deliverables |
| --- | --- | --- |
| **Kasule Arnold** | Math engine for Gradient Descent: the cost function (error) and the gradient vector (slope of the error), so the model knows which direction to adjust its weights | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Rubangakene Joshua** | Gradient Descent training loop built on Arnold's gradient code: takes small steps down the error surface using a learning rate until the error is lowest and the best weights are found | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Kyamulabi Priscilla** | Loss-tracking functions that record how the error shrinks across training epochs, to confirm the model converges | `include/poly_reg/polynomial_regression.hpp`, `src/polynomial_regression.cpp` |
| **Tanga Ibrahim** | Optimizes the feature expansion pipeline so expanded design matrices scale efficiently during iterative batch training | `include/poly_reg/feature_expansion.hpp`, `src/feature_expansion.cpp` |
| **Anzoa Pruna** | Extends the file-handling utilities to route input files and export prediction results to `data/output/` | `include/poly_reg/csv_loader.hpp`, `src/csv_loader.cpp`, `data/output/` |
| **Gidudu Allan Bright** | Final user instructions in the README: how to build the project and run both the OLS and Gradient Descent demos from the terminal | `README.md` |
| **Christine Hannah Adong** | Updates `CMakeLists.txt` to compile the final executable targets, reviews and merges all final Pull Requests, compiles the final group status report, updates the README, added more demo examples (ascii graph, gradient descent, preprocessing export) | `CMakeLists.txt`, `reports/week-04.md`, `README.md` |

---

## Git Workflow

The `main` branch is protected. Nobody pushes to it directly, and every change goes through a Pull Request that must be approved before merging. Christine reviews and merges PRs into `main`.

1. **Update your local copy**

   ```bash
   git status
   git pull main
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