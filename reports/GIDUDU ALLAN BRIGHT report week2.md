# Week 2 Report: Allan

**Project:** Polynomial Regression from Scratch (Machine Learning 7)
**Member:** Allan
**Role this week:** Test datasets and README documentation
**Branch:** `feature/<branch-name>`
**Pull Request:** `<PR link>`

---

## 1. Assigned Tasks

1. Prepare test datasets with varying polynomial degrees (d = 1, 2, 3, 4, 5) in `data/input/`, to demonstrate curve fitting and potential overfitting.
2. Update `README.md` with the execution commands showing how to run the full training and evaluation demo.

**Files:** `data/input/` datasets and `README.md`.

---

## 2. Work Completed

### 2.1 README update

- Added a **Running the Training and Evaluation Demo** section with commands to:
  - train and evaluate on a single dataset with a chosen degree;
  - run all five datasets with their matching degree;
  - compare underfitting, a good fit and overfitting by fitting one dataset with different degrees;
  - inspect the saved `data/output/predictions.csv`;
  - run the regression tests (`test_regression`).
- Extended **Sample Data** with a table of the five degree-specific datasets and an explanation of underfitting and overfitting.
- Added the Week 2 modules to **Module Overview**: feature expansion, polynomial regression (`XᵀX`, `β`, MSE, RMSE) and CSV export.
- Updated **Project Structure**, **Running Tests** and the **Table of Contents** to include the new files, `data/output/` and `test_regression`.
- Added a **Team Roles (Week 2)** table listing each member's task and files.

### 2.2 Test datasets

- Datasets for d = 1 to 5 in `data/input/`: `poly_degree1.csv` to `poly_degree5.csv`.
- Format follows the project standard: numeric values only, comma-separated, feature `x` first and target `y` last, same number of columns in every row.
- Each dataset is generated from a known degree-d polynomial with a small amount of noise, so results can be compared against the true curve.

*(Fill in before submitting: the exact polynomials used, number of rows and noise level for each file.)*

| File | True degree | Rows | Noise |
| --- | --- | --- | --- |
| `poly_degree1.csv` | 1 | | |
| `poly_degree2.csv` | 2 | | |
| `poly_degree3.csv` | 3 | | |
| `poly_degree4.csv` | 4 | | |
| `poly_degree5.csv` | 5 | | |

---

## 3. How It Supports the Team

- Pruna's CSV export, Tatiana's MSE/RMSE and Joshua's coefficient solver can all be tried on datasets with a known true degree.
- Joseph's tests can use the same degree-2 and degree-3 data as ground truth.
- The underfitting and overfitting commands give the group a ready demo for the final presentation.

---

## 4. Challenges and Notes

- The demo commands depend on the final executable name and argument order from the CMake setup. They were written to match `poly_reg_demo <csv> <degree>` and must be checked against `CMakeLists.txt` once the Week 2 code is merged.
- Overfitting is clearest when the model is evaluated on held-out data, so the demo should be paired with the train/test split from Week 1.

*(Add any real problems you ran into.)*

---

## 5. Next Steps (Week 3)

- Verify every README command against the merged code and correct any mismatches.
- Add expected output (coefficients, MSE, RMSE) for each dataset once the pipeline runs end to end.
- Keep the header comments and documentation up to date as new modules are added.

---

## 6. AI Use Declaration

| Field | Details |
| --- | --- |
| **Tool** | Claude (Anthropic) |
| **Purpose** | Generated the five test datasets `poly_degree1.csv` to `poly_degree5.csv` in `data/input/`. |
| **Reason** | The datasets are synthetic: AI was used to produce data from known degree-d polynomials with a small amount of added noise, which is faster and more consistent than writing about five files of values by hand, and gives a known true curve to compare the fitted results against. |
| **Human review** | The generated datasets were checked for the required format (numeric, comma-separated, `x` first and `y` last, equal column counts) and the README and report text were reviewed against the Week 2 task list and edited by me before submission |

---

## 7. Git Contributions

| Commit | Description |
| --- | --- |
| `<hash>` | `<e.g. Add test datasets for degrees 1 to 5>` |
| `<hash>` | `<e.g. Update README with Week 2 demo commands>` |
