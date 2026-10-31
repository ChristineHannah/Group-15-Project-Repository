#pragma once
#include <string>
#include "poly_reg/matrix.hpp"

namespace PolyReg {
class CSVLoader {
public:
    // Reads numeric data from a CSV file and returns it as a Matrix
    static Matrix load_dataset_from_csv(const std::string& file_path);

    // Writes true target values and model prediction results into a CSV file

    static void export_predictions_to_csv(const std::string& output_path, const Matrix& y_true, const Matrix& y_pred);
};
} // namespace PolyReg