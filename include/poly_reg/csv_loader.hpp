#pragma once

#include <string>
#include "poly_reg/matrix.hpp"

namespace PolyReg {

class CSVLoader {
 // namespace PolyReg
public:
    /**
     * Opens a CSV file, parses comma-separated numeric features and target variables,
     * handles file stream errors, and loads the data into a Matrix object.
     */
    static Matrix load_dataset_from_csv(const std::string& file_path);
};

} // namespace PolyReg