Name: Anzoa Pruna 
Role: CSV Dataset loading

Summary of completed Deliverables
Maintained the CSVLoader class declaration in the .hpp file and its implementation in the .cpp file.
Retained the static member function (load_dataset_from_csv()) developed previously to support importing numerical datasets from CSV files.
Implemented a new static member function, export_predictions_to_csv(), to export actual target values and model predictions to a CSV file.
Designed the export function to accept an output file path and two constant references to Matrix objects representing the true target values and predicted values.
Implemented validation to ensure that the target and prediction matrices have identical row counts before exporting the data.
Added exception handling using (std::invalid_argument) to report situations where the target and prediction matrices contain different numbers of rows.
Implemented output file handling using std::ofstream and added check to ensure that the output file opens successfully.
Set up the exporter to generate a CSV header containing two columns , y_true and y_pred.
Implemented a loop to write the actual target values and their corresponding predicted values into the output file, seperating the two values with commas.
Used the get_rows() member function to determine the number of rows to export and the at() member function to retrieve the values from the target and prediction matrices.
Added exception handling std::runtime_error to report problems when opening the output file.
Closed the output file using output_stream.close() after writing the predictions.
Continued using the existing Matrix class to represent the numerical data,maintaining consistency between the CSV import and export operations.


Created class
The CSVLoader class now contains two public static member functions, the load_dataset_from_csv(const std::string& file_path) and the added export_predictions_to_csv(const std::string& output_path, const Matrix& y_true, const Matrix& y_pred) which exports actual target values and model predictions to a CSV file. It accepts the output file path and two matrices containing the actual and predicted values.


Why was the class created?
The class provides a reusable mechanism for importing datasets and exporting predictions while keeping file-handling operations separate from the main regression calculations.

The existing import functionality allows numerical datasets to be loaded from CSV files and converted into "Matrix" objects for further processing. The new "export_predictions_to_csv()" function addresses this requirement by writing both sets of values into a structured CSV file. This supports the inspection and comparison of actual and predicted values.


What data does the class hold?
The class does not declare variables or data members. Instead, the variables used during dataset import and export of prediction are local to their particular functions.


What functions operate on that data?
load_dataset_from_csv(). This function handles importing numerical data from CSV files. 
export_predictions_to_csv(). This function handles exporting actual values and predictions to a CSV file.


Why are some members private and others public? 
The CSVLoader class has two staic public member functions. They are public because other components of the program need to access the dataset import and prediction export operations. They can be called directly through the class name without creating a CSVLoader object using the "static" component. The class doesnot haqve private or protected members.


How is the class used by the rest of the program?
The class interacts with the Matrix class. During import, it creates a matrix. During export, it uses the matrix's public member functions (get_rows() and at()) to retrieve values that must be written to the output file.


Encapsulation
Encapsulation means protecting data inside a class by controlling how it can be accessed. This is shown through the organization of the dataset import and prediction export within the CSVLoader class. 

Inheritance
Inheritance allows a class to acquire the attributes of another class. It is not demonstrated for this particular class.

Polymorphism
This allows a common interface to support different implementation. It also is not demonstrated.


AI Transparency
ChatGPT was used to understand the new changes that were needed in the program. it was also used to provide the step by step instructions to implement the changes and provide the skeleton of the code.

ChatGPT also helped with the layout used to write this report.

CSVLoader class layout
[class layout](AnzoaPruna_CSVLoader_classlayout.jpg)











