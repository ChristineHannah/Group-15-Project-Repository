#include "poly_reg/csv_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cctype>
#include <algorithm>

namespace PolyReg {

Matrix CSVLoader::load_dataset_from_csv(const std::string& file_path) {
    std::ifstream file_stream(file_path);

    // Edge Case 1: File could not be opened or found
    if (!file_stream.is_open()) {
        throw std::runtime_error("Error: Could not open dataset file at path: " + file_path);
    }

    std::string current_line;
    std::vector<std::vector<double>> parsed_row_collection;
    int expected_column_count = -1;
    int line_number = 0;

    while (std::getline(file_stream, current_line)) {
        line_number++;

        // Skip empty lines or lines containing only whitespace
        if (current_line.empty() || std::all_of(current_line.begin(), current_line.end(), [](unsigned char c){ return std::isspace(c); })) {
            continue;
        }

        // Skip CSV header rows if they contain alphabetical characters (e.g., "x,y" or "feature,target")
        if (line_number == 1 && std::isalpha(static_cast<unsigned char>(current_line[0]))) {
            continue;
        }

        std::stringstream line_stream(current_line);
        std::string cell_value_str;
        std::vector<double> current_row_values;

        while (std::getline(line_stream, cell_value_str, ',')) {
            // Trim leading and trailing whitespace around each cell value
            size_t first_non_space = cell_value_str.find_first_not_of(" \t\r\n");
            if (first_non_space == std::string::npos) {
                continue; // Skip empty cells
            }
            size_t last_non_space = cell_value_str.find_last_not_of(" \t\r\n");
            std::string cleaned_cell = cell_value_str.substr(first_non_space, (last_non_space - first_non_space + 1));

            try {
                // Edge Case 2: Handle floating-point numeric conversions and check for malformed data
                size_t characters_processed = 0;
                double numeric_value = std::stod(cleaned_cell, &characters_processed);
                
                if (characters_processed != cleaned_cell.size()) {
                    throw std::invalid_argument("Malformed non-numeric token detected.");
                }

                current_row_values.push_back(numeric_value);
            } catch (const std::exception&) {
                throw std::runtime_error("Error: Failed to parse numeric value '" + cleaned_cell + 
                                         "' on line " + std::to_string(line_number) + " of file " + file_path);
            }
        }

        if (current_row_values.empty()) {
            continue;
        }

        // Edge Case 3: Verify consistent row widths across the entire dataset
        if (expected_column_count == -1) {
            expected_column_count = static_cast<int>(current_row_values.size());
        } else if (static_cast<int>(current_row_values.size()) != expected_column_count) {
            throw std::runtime_error("Error: Inconsistent row length detected on line " + std::to_string(line_number) + 
                                     ". Expected " + std::to_string(expected_column_count) + 
                                     " columns, but found " + std::to_string(current_row_values.size()) + ".");
        }

        parsed_row_collection.push_back(current_row_values);
    }

    file_stream.close();

    // Edge Case 4: Ensure the file contained valid numeric rows
    if (parsed_row_collection.empty()) {
        throw std::runtime_error("Error: Dataset file contains no valid numeric data rows: " + file_path);
    }

    int total_rows = static_cast<int>(parsed_row_collection.size());
    int total_cols = expected_column_count;

    // Construct the final Matrix object and populate it safely using encapsulation
    Matrix loaded_dataset_matrix(total_rows, total_cols);

    for (int r = 0; r < total_rows; ++r) {
        for (int c = 0; c < total_cols; ++c) {
            loaded_dataset_matrix.at(r, c) = parsed_row_collection[r][c];
        }
    }

    return loaded_dataset_matrix;
}

} // namespace PolyReg