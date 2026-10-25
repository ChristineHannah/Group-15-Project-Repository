# Individual Progress Report - Week 04
**Name:** Allan  
**Role / Module:** Allan - Documentation (final user instructions in `README.md`)  
**Date:** October 2026  

---

## 1. Summary of Completed Deliverables
* Wrote the final user instructions in `README.md`, explaining how to build the project with CMake and how to run both the OLS (Normal Equation) and Gradient Descent demos from the terminal.
* Added a new section, **Running the Gradient Descent Demo**, with step-by-step commands: build, run OLS, run Gradient Descent (input file, degree, solver, learning rate, epochs), compare the two solvers, check convergence, check `data/output/predictions.csv`, and run all tests with CTest.
* Updated the README introduction, project objective, module overview, project structure and test list to include Gradient Descent, `test_gradient_descent.cpp`, `examples/polynomial_regression_demo.cpp` and `reports/week-04.md`.
* Added an **Example Use Cases** section showing what the library does for prediction: fitting a curve and predicting new values, choosing the polynomial degree (underfitting vs overfitting), and solving the same problem with OLS and Gradient Descent. The values shown were calculated with the Normal Equation on a small sample dataset.
* Added an **External Testing** section to the README with testing steps and a results table for testers outside our team.
* Added the Week 4 team roles table and updated the table of contents.
* Added a Gradient Descent troubleshooting table (diverging loss or `nan`, slow convergence, higher degrees not converging).
* Verified the build and demo commands against the project's CMake configuration: *(confirm after the final merge)*.

---

## 2. Object-Oriented Class Breakdown (Lecturer's Guidelines)

### **1. What class did you create?**
* **Answer:** I did not create a new class this week. My role was documentation, so my deliverable is `README.md`. It documents the Week 4 Gradient Descent work that my teammates added in `include/poly_reg/polynomial_regression.hpp` and `src/polynomial_regression.cpp`, and the optimized feature expansion in `include/poly_reg/feature_expansion.hpp`.

### **2. Why?**
* **Answer:** The README is how a new user learns to build and run the project. It explains the two solvers (Normal Equation and Gradient Descent) and how the classes fit together, so the library can be used without reading the source code.

### **3. What data does it hold?**
* **Answer:** Not applicable, since I wrote no class. The README describes the data the program works with: input CSV files in `data/input/` (`x,y` columns), the expanded design matrix, the weights `β`, the loss recorded at each epoch, and the prediction output in `data/output/predictions.csv` (`x, y_actual, y_predicted`).

### **4. What functions operate on that data?**
* **Answer:** Not applicable to my deliverable. The README documents the functions my teammates wrote: the cost function and gradient vector (Arnold), the Gradient Descent training loop with a learning rate (Joshua), loss tracking across epochs (Tatiana), optimized feature expansion (Ibrahim), and file input and output routing (Pruna).

### **5. Why are some members private and others public? How is the class used by the rest of the program?**
* **Answer:** Not applicable, since I wrote no class. In the Coding Guidelines section, the README states that headers carry documentation comments for each class and function, and that errors are handled with exceptions. The demo program uses the library through its public interface only: it loads the CSV, expands the features, trains with the chosen solver, predicts, scores (MSE and RMSE) and exports the results.

---

## 3. Challenges & Solutions
* **Challenge:** The Gradient Descent code was being written by several teammates in parallel, so the exact demo command (argument order, learning rate and epoch values) had to be confirmed against the final code before the instructions could be finalized.
* **Solution:** Wrote the commands from the agreed project structure, then checked them against the merged code and CMake targets. Added a troubleshooting table for the cases where Gradient Descent behaves differently across datasets, such as a learning rate that is too large or too small.



## 4. AI Tool Transparency
* **Tool Used:** Claude (Anthropic) was used to generate the examples fto show what the program does and to predict the use cases and values together with the actual values.
