# Individual Progress Report - Week 02
Name: KYANKYA JOSEPH
Role / Module: Kyankya Joseph - Unit Test Suites


# 1. Summary of Completed Deliverables

I updated the two test files from Week 1 on the branch KyankyaJoseph-Week2 and opened a Week 2 pull request.

A. test_matrix.cpp (updated)
1. Construction and element access: it creates a 2x3 matrix, then checks the number of rows and columns.
2. Arithmetic: checks addition, subtraction , multiplication and transpose on 2x2 matrices.
3. Determinant and inverse: checks that the determinant of the matrix is 10, then multiplies the matrix by its inverse and checks that the result is the identity matrix.
4. Exception handling: checks that adding matrices of different sizes throws an error, and that inverting a singular matrix throws an error.

B. test_preprocessing.cpp (updated)
1. Min-max scaling: checks that 10, 20, 30 become 0, 0.5, 1.
2. Z-score standardization: checks that the mean of the standardized values is about 0.
3. Train/test split: checks that 10 rows with a 0.8 ratio give 8 training rows and 2 test rows.
4. CSV loader: loads data/input/quadratic_clean.csv and checks that it has rows and two columns. If the file is not found, the test prints a message instead of failing.

# 2. Object-Oriented Class Breakdown 

1. What class did you create?
Answer: I did not create a class. I wrote test functions, each one testing a part of the classes my group wrote: Matrix, Preprocessing and CSVLoader in the PolyReg namespace. A helper function and a main function that calls all the tests complete each file.

2. Why?
Answer:My role in the group is testing. The tests check that the group's code gives correct answers, using small examples where I already know the result.

3. What data does it hold?
Answer:My test files hold no data of their own ecept the small matrices created inside each test. The classes they test hold numbers arranged in rows and columns for example a single column of values for scaling and a grid of numbers for matrix math.

4. What functions operate on that data?
Answer: The tests call get_rows(), get_cols(), at(), add(), subtract(), multiply(), transpose(), compute_determinant() and compute_inverse() on Matrix. They call compute_min_max_scaling(), compute_z_score_standardization() and split_train_test_data() from Preprocessing, and load_dataset_from_csv() from CSVLoader.

5. Why are some members private and others public? How is the class used by the rest of the program?
Answer: The tests only use public functions, since code outside a class cannot reach private members.  The rest of the program uses Matrix through its public functions.

Inheritance and polymorphism: I have not yet checked whether the group’s classes use inheritance or virtual functions.

# 3. Challenges & Solutions
Challenge:Running git fetch --all gave an error about branch names that differ only in capital letters, because Windows treats them as the same.
Solution: I fetched only the branch I needed (main) instead of all branches.
Challenge:My project folder had old .exe files from earlier test builds, and they could have been committed by mistake.
Solution:I added only the specific test files with git add, never the whole folder, and checked git status before every commit.

# 4. AI Tool Transparency
Tool Used: The Week 2 test files were generated with Claude, I did not write the test code myself.
Claude helped with Git commands to submit the work. 
