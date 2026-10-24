#pragma once
#include <string>
#include "poly_reg/matrix.hpp"

namespace PolyReg {

class CSVLoader {
public:
    /**
     * Reads a comma-separated CSV file from disk into a Matrix container.
     */
    static Matrix load_dataset_from_csv(const std::string& file_path);

    /**
     * Writes true target values and model predictions into a CSV file.
     * Generates a 2-column CSV: y_true, y_pred
     */
    static void export_predictions_to_csv(const std::string& output_path, const Matrix& y_true, const Matrix& y_pred);
};

} // namespace PolyReg