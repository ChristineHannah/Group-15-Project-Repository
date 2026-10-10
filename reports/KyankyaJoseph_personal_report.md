# Personal Report

Name: Kyankya Joseph
Role: Test Suite Developer
Branch: KyankyaJosephRedo

## What I Did

1. Branch Setup and Repository Sync: Pulled the latest changes from the main branch and created a dedicated working branch named KyankyaJosephRedo to keep my work isolated and clean.
2. Rewrote Matrix Test Suite: Created a simplified test suite in tests/TestMatrix.cpp using foundational C++ concepts from Chapters 1 through 8 of Stroustrup's book, covering construction, element access, matrix math, transpose, and error handling.
3. Rewrote Preprocessing Test Suite: Created tests/TestPreprocessing.cpp to test feature scaling (standardize and minmax_scale) and dataset splitting (train_test_split).
4. Local Compilation and Verification: Manually compiled and executed both test suites using MinGW g++ 6.3 (-std=c++14) in PowerShell, ensuring all 18 matrix checks and 18 preprocessing checks passed cleanly.
5. Version Control and Pull Request: Staged, committed, pushed my branch to GitHub, and prepared a clean pull request for group review along with this report.


## Deliverables

1. tests/TestMatrix.cpp
   Rewrote matrix tests using foundational C++ concepts from Chapters 1 through 8 of Bjarne Stroustrup's book. The suite checks matrix construction, element read and write access, arithmetic operations (+, -, *), matrix transposition, and exception throwing for invalid dimensions or out-of-bounds access. All 18 checks compiled cleanly and passed.

2. tests/TestPreprocessing.cpp
   Rewrote preprocessing tests to cover feature scaling (standardize and minmax_scale) as well as dataset splitting (train_test_split). Verified edge cases such as constant columns, empty matrices, and valid split ratios without data loss. All 18 checks compiled cleanly and passed.


## Challenges and Solutions

1. Header Include Path Discrepancy
   Issue: Line 1 of src/preprocessing.cpp uses `#include "preprocessing.hpp"` instead of `"poly_reg/preprocessing.hpp"`. Standard include flags failed to locate the header.
   Solution: Added `-Iinclude/poly_reg` as an extra include flag in the g++ PowerShell compilation command.

2. Linker Errors During Preprocessing Compilation
   Issue: Compiling TestPreprocessing.cpp with src/preprocessing.cpp resulted in undefined reference errors for poly_reg::Matrix member functions.
   Solution: Included src/matrices.cpp in the g++ command alongside src/preprocessing.cpp so the compiler could link the Matrix class methods.


## AI Usage Declaration

Tools Used: Claude (Anthropic) and Gemini (Google)

Purpose:
- Troubleshooting MinGW g++ compilation flags and resolving linker errors in PowerShell.
- Formulating exact Git terminal commands for branching, committing, pushing, and updating pull requests.
- Structuring Markdown reports and formatting documentation clearly.

Declaration:
AI assistants were used strictly as virtual tutors for terminal guidance, debugging assistance, and document formatting. All test logic, compilation commands, and assertions were executed, tested, and verified manually on my local Windows environment.

---

## References

1. Stroustrup, Bjarne. Programming: Principles and Practice Using C++ (3rd Edition), Chapters 1 to 8.