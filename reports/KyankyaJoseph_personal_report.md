# Personal Report by Kyankya Joseph

Group 15, Polynomial Regression C++ Library
Role: writing the test suites

## Completed Deliverables

Week 1 (merged into main):
- tests/test_matrix.cpp - tests for the Matrix class: creating matrices, reading and writing elements, addition, subtraction, scalar and matrix multiplication, transpose, and bad inputs that should throw errors.
- tests/test_preprocessing.cpp - tests for Standardize, MinmaxScale and TraintestSplit, including empty matrices and columns where every value is the same.

Week 2 (branch KyankyaJoseph, pull request open):
- tests/test_matrix_inverse.cpp - determinant and inverse tests.
- tests/test_csv_loader.cpp - CSV loading tests.
- tests/test_features.cpp - polynomial feature tests.

The three Week 2 tests print SKIPPED and exit with 0 because the code they test is not on main yet. They will run normally once it is added.

## Challenges and Solutions

The inverse and determinant code was in a separate Matrix class, and there was no CSV loader or polynomial feature code on GitHub. I wrote the tests so they skip until that code exists, so they do not break the build.

The preprocessing code I received had compile errors: "| |" instead of "||", a parameter called max_value that was used as max_val, a missing "{" in TraintestSplit, and a missing closing brace for the namespace. I listed these for the author to fix.

src/preprocessing.cpp included "preprocessing.hpp" but the header is in include/poly_reg/, so the compiler could not find it. I added an extra -I option to compile and told the team.

My g++ is version 6.3 and I do not have CMake, so I compiled with g++ -std=c++14.

I also had Git problems. I first ran commands outside the cloned folder and got "not a git repository". Later a pull request showed no changes because the test file had already reached main, so I started a new branch from an updated main.

## AI Transparency

Claude: drafted the test files above, explained the Git and compile commands step by step, helped find the compile errors and the include problem, and suggested wording for the pull request descriptions, which I edited.

Gemini: helped with the Git steps for the branch tests/preprocessing-suite-v2 (creating the branch, committing and pushing) and with the pull request title and description.

## What I did myself:
 I cloned the repository in VS Code, created the branches, and moved the test files into the tests folder. I compiled and ran every test on my own computer and checked the results. I made the commits and pushes, opened the pull requests, wrote the pull request descriptions in my own words, and messaged the group leader and teammates about the missing code.

## References

Stroustrup, B. Programming: Principles and Practice Using C++ (3rd edition), course textbook.
