#pragma once
#include <string>
#include "poly_reg/matrix.hpp"

namespace PolyReg {
class CSVLoader {
public:
    /**
     * Opens a CSV file, parses comma-separated numeric features and targets,
     * and loads them into a Matrix object.
     */
    static Matrix load_dataset_from_csv(const std::string& file_path);

    /**
     * Writes true target values and model prediction results into a CSV file.
     */
    static void export_predictions_to_csv(const std::string& output_path, const Matrix& y_true, const Matrix& y_pred);
};
} // namespace PolyReg