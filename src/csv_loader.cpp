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
    if (!file_stream.is_open()) {
        throw std::runtime_error("Error: Could not open dataset file at path: " + file_path);
    }

    std::string current_line;
    std::vector<std::vector<double>> parsed_row_collection;
    int expected_column_count = -1;
    int line_number = 0;

    while (std::getline(file_stream, current_line)) {
        line_number++;
        if (current_line.empty() || std::all_of(current_line.begin(), current_line.end(), [](unsigned char c) { return std::isspace(c); })) {
            continue;
        }
        if (line_number == 1 && std::isalpha(static_cast<unsigned char>(current_line[0]))) {
            continue; // Skip header row
        }

        std::stringstream line_stream(current_line);
        std::string cell_value_str;
        std::vector<double> current_row_values;

        while (std::getline(line_stream, cell_value_str, ',')) {
            size_t first_non_space = cell_value_str.find_first_not_of("\t\r\n ");
            if (first_non_space == std::string::npos) continue;
            size_t last_non_space = cell_value_str.find_last_not_of("\t\r\n ");
            std::string cleaned_cell = cell_value_str.substr(first_non_space, (last_non_space - first_non_space + 1));

            try {
                size_t chars_processed = 0;
                double numeric_value = std::stod(cleaned_cell, &chars_processed);
                if (chars_processed != cleaned_cell.size()) {
                    throw std::invalid_argument("Malformed non-numeric token.");
                }
                current_row_values.push_back(numeric_value);
            } catch (const std::exception&) {
                throw std::runtime_error("Error: Failed to parse numeric value on line " + std::to_string(line_number) + " of file " + file_path);
            }
        }

        if (current_row_values.empty()) continue;

        if (expected_column_count == -1) {
            expected_column_count = static_cast<int>(current_row_values.size());
        } else if (static_cast<int>(current_row_values.size()) != expected_column_count) {
            throw std::runtime_error("Error: Inconsistent row length detected on line " + std::to_string(line_number));
        }

        parsed_row_collection.push_back(current_row_values);
    }
    file_stream.close();

    if (parsed_row_collection.empty()) {
        throw std::runtime_error("Error: Dataset file contains no valid numeric rows: " + file_path);
    }

    int total_rows = static_cast<int>(parsed_row_collection.size());
    int total_cols = expected_column_count;
    Matrix loaded_dataset_matrix(total_rows, total_cols);

    for (int r = 0; r < total_rows; ++r) {
        for (int c = 0; c < total_cols; ++c) {
            loaded_dataset_matrix.at(r, c) = parsed_row_collection[r][c];
        }
    }
    return loaded_dataset_matrix;
}

void CSVLoader::export_predictions_to_csv(const std::string& output_path, const Matrix& y_true, const Matrix& y_pred) {
    if (y_true.get_rows() != y_pred.get_rows()) {
        throw std::invalid_argument("Error: Target and prediction matrix row counts must match for CSV export.");
    }

    std::ofstream output_stream(output_path);
    if (!output_stream.is_open()) {
        throw std::runtime_error("Error: Could not open output file for writing at path: " + output_path);
    }

    output_stream << "y_true,y_pred\n";
    int total_rows = y_true.get_rows();
    for (int r = 0; r < total_rows; ++r) {
        output_stream << y_true.at(r, 0) << "," << y_pred.at(r, 0) << "\n";
    }
    output_stream.close();
}
} // namespace PolyReg