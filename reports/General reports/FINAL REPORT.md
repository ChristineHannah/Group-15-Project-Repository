# Final Project Report - Group 15
**Project:** Polynomial Regression from Scratch in C++17  
**Date:** November 2026  
**Group Leader:** Christine Hannah Adong  

---

## 1. Executive Summary
Honestly, this project has been a massive uphill battle. Building a machine learning library completely from scratch in C++ without using any external packages like Eigen or standard ML libraries tested every single nerve we had as a group. Over these past four weeks, we went from arguing over basic matrix multiplication loops to actually getting OLS normal equations and gradient descent working. Week 4 was mostly just running final tests, fixing some minor memory and assertion bugs, and triple-checking that everything compiles cleanly without throwing weird runtime exceptions. But somehow, it actually works.

---

## 2. Individual Contributions & Module Breakdown

Here is what everyone actually did, because dividing this work was honestly chaotic:

* **Christine Hannah Adong (Leader):** Set up the initial repo structure, fought with CMakeLists.txt when it kept refusing to link the headers, merged all the PRs (usually with merge conflicts), and somehow put these reports together.
* **Kasule Arnold:** Built the base Matrix class in weeks 1 and 2, and then helped set up the transpose and $X^T X$ matrix product logic for the OLS and gradient descent cost functions.
* **Rubangakene Joshua:** Took Arnold's matrix code and implemented the scary linear algebra solvers—determinants, Gauss-Jordan matrix inversion, and solving the normal equations $\beta = (X^T X)^{-1} X^T y$. 
* **Kyamulabi Tatiana:** Handled the preprocessing side of things (Min-Max scaling and Z-score standardization) and wrote the MSE/RMSE loss evaluation metrics so we could actually tell if our model's predictions were trash or not.
* **Anzoa Pruna:** Wrote the CSV loader and the prediction exporter. Dealing with string streams, commas, and weird line endings in CSV files gave her headaches, but she got it parsing cleanly.
* **Tanga Ibrahim:** Built the polynomial feature expansion module. It takes raw 1D inputs and turns them into multi-column design matrices ($[1, x, x^2, \dots, x^d]$) so we can fit curves instead of just straight lines.
* **Gidudu Allan:** Gathered the datasets (quadratic and cubic CSV files) and tried his best to make the README documentation readable before the deadline.
* **Kyankya Joseph:** Wrote all the unit and integration tests (`test_matrix.cpp`, `test_preprocessing.cpp`, `test_regression.cpp`, and `test_gradient_descent.cpp`). He kept catching our math bugs with `assert()` every time we thought we were done.

---

## 3. Results & Integration (Testing Other Teammates' Work)

During Week 4, we didn't add any crazy new features. We mostly focused on integration testing, making sure everyone's pieces actually fit together without crashing. These are some of the results from different people running the code.

From Kyankya Joseph;


![alt text](<images for final/Kyankya's image.jpg>)


From Kyamulabi Priscilla;


![alt text](<images for final/Tatiana's image 1.jpg>)



![alt text](<images for final/Tatiana's image 2.jpg>)



---

## 4. Challenges & How We Survived Them

* **Matrix Inversion Singularities:** Early on, Joshua's inverse function kept throwing runtime errors because unscaled polynomial features made matrices ill-conditioned. Tatiana's preprocessing scaler saved us by keeping numbers small and stable.
* **Git Merge Conflicts:** Every single week, at least two people touched `matrix.cpp` or `CMakeLists.txt` at the same time, leading to terrible merge conflicts. We had to learn how to do local pulls and stash changes properly.

---

## 5. AI Tool Usage Declaration
* **Tools Used:** Gemini / ChatGPT (used strictly for debugging weird C++17 compilation errors, checking matrix pivoting logic syntax, and figuring out why CMake was throwing configuration cache errors).
* **Reason:** None of us are professional C++ library developers, so we needed help understanding standard exception handling and Stroustrup-compliant encapsulation rules. All core code was reviewed, tested, and integrated by the team.