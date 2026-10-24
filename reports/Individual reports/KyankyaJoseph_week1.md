# Individual Progress Report - Week 01
**Name:** KYANKYA JOSEPH
**Role / Module:** Kyankya Joseph - Unit Test Suites  

# 1. Summary of Completed Deliverables
A. test_preprocessing.cpp⁠ 
This file tests functions that prepare data before it is used in machine learning models
functions
1. Min-Max Scaling Test: This checks if data features are correctly scaled to fit in a range between ⁠0 and ⁠1. 
2. Z-Score Standardization Test: This checks if data is centered around a mean of ⁠0.0⁠.  
3. Train-Test Split Test: Is checks if a dataset can be properly divided into training data for teaching the model and testing data for evaluating it
B. ⁠test_matrix.cpp⁠ (Matrix Math Tests)
This file tests the linear algebra operations needed to process the data and calculate regression model.
functions
1. Construction & element access: it tests the ability of creating matrices of specific dimensions and reads values at given row and column indexes.  
2. Addition & Multiplication: it tests adding and and multiplying matrices.  
3. Transpose: it basically swaps rows and columns
4. Determinant & Inverse: it is for calculating a matrix's determinant and inverse.  It checks that the determinant equals to 10 and that matrix times inverse gives the identity matrix.
5. Exception Handling: it checks adding different sizes of matrices throws errors

# 2. Object-Oriented Class Breakdown (Lecturer's Guidelines)

What class did you create?
Answer:We created and tested elemnets within the PolyReg namespace, focusing on matrix structures and preprocessing data.
Why?
Answer:We need these tools to clean and scale data and do basic math so our program can run polynomial regression correctly

What data does it hold?
Answer:The classes my tests use holds numbers arranged in rows and columns, like single columns of values for scaling and grids of numbers for math equations.

What functions operate on that data?
Answer:For data preparation, it has functions to scale numbers between 0 and 1, standardize them, and split data into training and testing sets. For matrices, it has functions to look up numbers, add them, multiply them, flip rows and columns, and find determinants and inverses

Why are some members private and others public? How is the class used by the rest of the program?
Answer:Private parts keep the internal data safe so other code cannot accidentally break it. Public parts give a safe way for the rest of the program to use the tools. The program uses these public tools to process data and run tests.

# 3. Challenges & Solutions
Challenge:I struggled a lot with tricky code bugs and had a hard time pushing my work to GitHub.
Solution:I used AI to help me find and fix the bugs in the code, and it also guided me step-by-step on how to successfully upload my work to GitHub.

# 4. AI Tool Transparency
Tool Used:Gemini AI and Claude AI used to assist in debugging code, resolving GitHub upload issues. Claude was used to provide the skeleton of the code, generate the C++ source files, and give the instructions needed to create a branch and push work to the repository.
