#include "poly_reg/csv_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cctype>
#include <algorithm>

namespace PolyReg {
    // Reads numeric data from a CSV file and returns it as a Matrix
Matrix CSVLoader::load_dataset_from_csv(const std::string& file_path) {
    std::ifstream file_stream(file_path); // Open CSV file for reading
    if (!file_stream.is_open()) {
        throw std::runtime_error("Error: Could not open dataset file at path: " + file_path);  // Error message if file cannot open
    }

    std::string current_line;  // Stores the line currently being read from the file
    std::vector<std::vector<double>> parsed_row_collection; // Temporarily stores all successfully parsed rows before creating the Matrix
    int expected_column_count = -1; // Number of columns has not been determined hence the -1
    int line_number = 0;  // Tracks the current line number so that errors can easily be identified

    while (std::getline(file_stream, current_line)) {  // Read file one line at a time 
        line_number++;  // Update line number
        if (current_line.empty() || std::all_of(current_line.begin(), current_line.end(), [](unsigned char c) { return std::isspace(c); })) {
            continue; // Skip lines that are empty or contain only whitespace
        }
        if (line_number == 1 && std::isalpha(static_cast<unsigned char>(current_line[0]))) {
            continue; // Skip header row
        }

        std::stringstream line_stream(current_line); // Create a string stream for the current line so its comma-separated values can be read
        std::string cell_value_str;  // holds text of one CSV cell value at a time
        std::vector<double> current_row_values;    // stores numeric values parsed from the current line

        while (std::getline(line_stream, cell_value_str, ',')) {  // Split the line at commas and read each cell value separately
            size_t first_non_space = cell_value_str.find_first_not_of("\t\r\n ");   // Find the first character that is not whitespace, tab, return or newline
            if (first_non_space == std::string::npos) continue;  // Ignorre a cell with only whitespace
            size_t last_non_space = cell_value_str.find_last_not_of("\t\r\n ");  //Find last character that is not whitespace, tab, return or newline
            std::string cleaned_cell = cell_value_str.substr(first_non_space, (last_non_space - first_non_space + 1));  //Remove whitespace from the beginning and end of the cell

            try {  // Tracks how many characters were used by std::stod when converting text to a numeric value. If not all characters were used, the cell is malformed and an error is thrown.
                size_t chars_processed = 0; // does the tracking of how many characters were processed by std::stod
                double numeric_value = std::stod(cleaned_cell, &chars_processed);  //Convert text to double
                if (chars_processed != cleaned_cell.size()) {  // Reject text if conversion did not consume the entire text, meaning that the cell contains non-numeric characters
                    throw std::invalid_argument("Malformed non-numeric token.");
                }
                current_row_values.push_back(numeric_value);  // Add converted numberto the current row
            } catch (const std::exception&) { // Error if cell cannot be parsed as a valid number
                throw std::runtime_error("Error: Failed to parse numeric value on line " + std::to_string(line_number) + " of file " + file_path);
            }
        }

        if (current_row_values.empty()) continue;  // Skip the line if no numeric values were collected from it

        if (expected_column_count == -1) {  // If this is the first valid row, set the expected column count based on its size
            expected_column_count = static_cast<int>(current_row_values.size());
        } else if (static_cast<int>(current_row_values.size()) != expected_column_count) {
            throw std::runtime_error("Error: Inconsistent row length detected on line " + std::to_string(line_number)); // Error if the current row does not match number of values in the first valid row
        }

        parsed_row_collection.push_back(current_row_values);   // Stores the current row of numeric values into the collection of all parsed rows
    }
    file_stream.close();  // Close file after reading is finished

    if (parsed_row_collection.empty()) {  // Error if no valid numeric rows were found in the file
        throw std::runtime_error("Error: Dataset file contains no valid numeric rows: " + file_path);  
    }

    // Determine number of rows and columns for the output Matrix 
    int total_rows = static_cast<int>(parsed_row_collection.size());
    int total_cols = expected_column_count;
    Matrix loaded_dataset_matrix(total_rows, total_cols); // Create Matrix with the dimensions of the parsed data

    for (int r = 0; r < total_rows; ++r) { // Copy each parsed values into the corresponding position in the Matrix
        for (int c = 0; c < total_cols; ++c) {
            loaded_dataset_matrix.at(r, c) = parsed_row_collection[r][c];  // At (r,c) accesses value at row r and column c
        }
    }
    return loaded_dataset_matrix;  // Return completed Matrix
}

// Writes true target values and model prediction results into the output CSV file
void CSVLoader::export_predictions_to_csv(const std::string& output_path, const Matrix& y_true, const Matrix& y_pred) {
    if (y_true.get_rows() != y_pred.get_rows()) {  // Ensure each row has an actual and predicted value to write to the output file
        throw std::invalid_argument("Error: Target and prediction matrix row counts must match for CSV export.");
    }

    std::ofstream output_stream(output_path);  // Open or create output CSV file for writing
    if (!output_stream.is_open()) { // Error if file cannot be opened for writing
        throw std::runtime_error("Error: Could not open output file for writing at path: " + output_path);
    }

    output_stream << "y_true,y_pred\n";  // Write CSV column headings as the first row
    int total_rows = y_true.get_rows();  // Get number of rows to export
    for (int r = 0; r < total_rows; ++r) {  // Write one actual value with its corresponding predicted value per row
        output_stream << y_true.at(r, 0) << "," << y_pred.at(r, 0) << "\n";  // Seperate the two values with a comma and end the row with a newline
    }
    output_stream.close();  // Close the output file after writing is complete
}
} // namespace PolyReg