#include "poly_reg/csv_loader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

namespace poly_reg 
{
    data CsvLoader::load(const string& filename, bool header){
        ifstream file {filename};
        if (!file.is_open()) {
            throw runtime_error("CsvLoader Error: Could not open file at " + filename);
        }
        
        data data_values;
        string line;
        size_t columns = 0;
        size_t rows = 0;
        
        if (header && getline(file, line)){
            rows++;
        }

        while (getline(file, line)) {
            rows++;
            if (line.empty()) continue;

            stringstream ss(line);
            string value;
            vector<double> current_row;

            while (getline(ss, value, ',')) {
                try{
                    current_row.push_back(stod(value));
                }
                catch(...) {
                    throw runtime_error("CsvLoader Error: Invalid data at row " + to_string(rows));
                }
            }

            if (current_row.empty()) continue;

            if (columns == 0) {
                columns = current_row.size();
            }
            else if (current_row.size() != columns) {
                throw runtime_error("CsvLoader Error: Inconsistent row length at row" + to_string(rows));
            }

            data_values.output.push_back(current_row.back());
            data_values.input.push_back(current_row);
        }

        file.close();
        return data_values;
    }


}

