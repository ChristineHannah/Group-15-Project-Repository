Name: Anzoa Pruna
Role: CSV dataset loading

Summary of completed deliverables
Declared the CSVLoader class int the header file (csv_loader.hpp) to provide functionality for loading datasets from CSV files.
Implemented the load_dataset_from_csv() static member function in the source file, csv_loader.cpp.
Used standard C++ libraries to support file handlingg, string processing, numeric conversion and error handling.
Implemented functionality to open CSV files, read their content line by line and parse comma seperated numeric values.
Added handling for empty lines and lines containing only whitespace to prevent them from being processed as valid data rows.
Implemented basic CSV header detection to skip a header row containing alphabeticalo characters.
Added whitespace trimming around individual cell values before converting them into numeric values.
Implemented error handling for files that cannot be opened, malformed numeric values, inconsistent row lengths and files containing no valid numeric data.
Ensured that valid rows contain a consistent number of columns before constructing the final dataset.
Stored the parsed dataset temporarily in two dimensional (std:vector<std::vector<double>>) container before transferring the values into a Matrix object.
Populated the final Matrix object using its constructor and bounds-checked at() member function, then returned the completed matrix to the calling program.

What class was created?
I created the CSVloader class within PolyReg namespace. The class is declared in the header file and implemented in the source file.

The class provides a static public member fuction. This function accepts the path of a CSV file as its argument, reads and processes the dataset and returns the loaded data as a Matrix object. it handles dataset loading.


Why the class was created?
The CSVLoader class was created to provide a way of importing numerical datasets from a CSV file into the polynomial regression 


What does the class hold?
The CSVLoader class holds variables that are declared locally inside the load_dataset_from_csv() function.
After the file has been processed successfully, the numerical values are transferred into a Matrix object named loaded_dataset_matrix.


What functions operate on the data?
the main function implemented in the CSVLoader class is load_dataset_from_csv(const std::string& file_path)


Why are some members private and others public? How is the class used by rest of the program?
The CSVLoader class does not declare private or protected members. It consists of a public static member function, load_dataset_from_csv().

The function is public because other components of the program need access to it. Declaring it as static allows the function to be called directly through the class name.


Challenges and solutions
The required work seemed complex in the beginning since CSV was an entirely new term. Used Google to properly understand what a CSV file was and to explain what the assignment entailed.

Creating a branch and pushing work to repository. ChatGPT was used to provide instructions to successfully push work.


AI transparency
Google to understand what the code was about.
ChatGPT to provide the skeleton of the code and the instructions needed to create a branch and push work to the repository.
























































































