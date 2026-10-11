# Week 1 Progress Report

**Member:** Allan **Role this week:** Base documentation, README skeleton, and sample datasets

## Completed

- Created four sample CSV datasets for testing polynomial regression, saved in `data/input/`:
  - `tiny_quadratic.csv`: exact quadratic with no noise, for checking results by hand
  - `quadratic_clean.csv`: quadratic with small noise
  - `cubic_noisy.csv`: cubic with heavier noise
  - `overfit_demo.csv`: few points with a roughly linear trend, for demonstrating overfitting
- Drafted the initial `README.md` (objective, prerequisites, group member roles, build steps, setup guidelines).
- Pushed the README and datasets to a new branch and opened a pull request.

## In Progress

- Adding documentation comment headers to the `.hpp` files as they are added by teammates.
- Filling in README sections that depend on code not yet written (usage, examples, how to run tests, limitations).

## Challenges/Blockers

- The README usage and run instructions cannot be finalized until the executable name and the main code are in place.
- The header files from teammates are not all merged yet, so header comments cannot be completed.

## Next Week

- Update the README with final build, usage, and test instructions once the matrix, CSV loader, and preprocessing modules are merged.
- Add the remaining header documentation comments.
- Add or adjust sample datasets if teammates' tests need different data.

## AI Use

- Tool: Claude
- Purpose: Generated the sample CSV datasets; explained my tasks and the Git workflow; explained the idea behind polynomial regression; produced an example README draft that I used only as a reference for what sections to cover
- Reason: To save time creating test data and to understand my tasks and the topic before starting. The final README was typed by me.
