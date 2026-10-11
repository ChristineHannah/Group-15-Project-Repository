#ifndef CSV_LOADER_HPP
#define CSV_LOADER_HPP

#include <string>
#include <vector>
using namespace std;


    struct data {
        vector<vector<double>> input;
        vector<double> output;
    };

    class CsvLoader {
        public:
         data load(const string& filename, 
            bool header = true);
    };



#endif