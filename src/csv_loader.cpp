#include "poly_reg/csv_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace poly_reg 
{
    Dataset CsvLoader::load(const string& filepath, bool has_header){
        ifstream file(filepath);
        if (!file.is_open()) {
            throw runtime_error("CsvLoader Error: Could not open file at " + filepath);
        }
        
        Dataset dataset;
        string line;
        size_t expected_columns = 0;
        size_t row_index = 0;
        
        if (has_header && getline(file, line)){
            row_index++;
        }

        while (getline(file, line)) {
            row_index++;
            if (line.empty()) continue;

            stringstream ss(line);
            string value;
            vector<double> current_row;

            while (getline(ss, value, ',')) {
                try{
                    current_row.push_back(stod(value));
                }
                catch(...) {
                    throw runtime_error("CsvLoader Error: Malformed data at row " + to_string(row_index));
                }
            }

            if (current_row.empty()) continue;

            if (expected_columns == 0) {
                expected_columns = current_row.size();
            }
            else if (current_row.size() != expected_columns) {
                throw runtime_error("CsvLoader Error: Inconsistent row length at row" + to_string(row_index));
            }

            dataset.targets.push_back(current_row.back());
            current_row.pop_back();
            dataset.features.push_back(current_row);
        }

        file.close();
        return dataset;
    }


}

