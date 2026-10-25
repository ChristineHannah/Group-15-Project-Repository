# Week 3 Report: Allan

**Project:** Polynomial Regression from Scratch (Machine Learning 7)
**Role this week:** Test datasets (d = 1, 2, 3, 4) and README demo instructions

## 1. Tasks assigned

- Prepare test datasets of polynomial degree d = 1, 2, 3 and 4 in `data/input/`.
- Update `README.md` with instructions for running the full training demo.

## 2. Work completed

### Datasets (`data/input/`)

| File | True degree | True coefficients (b0, b1, ...) | Rows |
| --- | --- | --- | --- |
| `week3_degree1.csv` | 1 | 1.5, 2.0 | 40 |
| `week3_degree2.csv` | 2 | 1.0, -2.0, 1.5 | 40 |
| `week3_degree3.csv` | 3 | 0.5, 1.0, -1.5, 0.8 | 40 |
| `week3_degree4.csv` | 4 | 2.0, 0.5, -3.0, -0.4, 0.6 | 40 |

- Format: header `x,y`, numeric values only, comma-separated, same column count on every row.
- `x` is evenly spaced from -2 to 2. `y` is the true polynomial plus Gaussian noise (standard deviation 0.3, fixed random seed so the files are reproducible).
- Sanity check: an independent least-squares fit of each file recovers coefficients close to the true values (for example, degree 2 gives about 1.03, -2.03, 1.45) with RMSE near 0.3, matching the noise level. These figures give Joseph and the team a reference for the expected weights.

### README.md

- Added a Week 3 roles table.
- Updated the Sample Data section with the four datasets above.
- Updated the demo section with the commands to train and evaluate on each dataset, the underfitting and overfitting comparison, and how to check `data/output/predictions.csv`.
- Written by hand by me, as the course requires.

## 3. Git activity

- Branch: `feature/week3-datasets-readme`
- Commits: dataset files, README update
- Pull Request opened to `main` for Christine's review.

## 4. Challenges

- Choosing noise and x-range so that degree 4 stays numerically stable when solving the Normal Equation.
- Keeping README commands consistent with the executable name and argument order used in `CMakeLists.txt`.

## 5. Plan for Week 4

- Re-run all datasets once every Week 3 module is merged, and update the README with the real output.
- Support final testing and documentation polish before the Nov 5, 2026 deadline.

## 6. AI use declaration

| Tool | Purpose | Reason |
| --- | --- | --- |
| Claude (Anthropic) | Generated the four synthetic CSV datasets with a script, and checked them with an independent least-squares fit | To save time producing reproducible noisy data and confirm it matches the true curves |
| Claude (Anthropic) | Drafted this weekly report | To structure the report; contents reviewed by me |

AI was **not** used to write `README.md`.
