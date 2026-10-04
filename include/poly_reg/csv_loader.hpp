#ifndef CSV_LOADER_HPP
#define CSV_LOADER_HPP

#include <string>
#include <vector>
using namespace std;

namespace poly_reg 
{
    struct Dataset {
        vector<vector<double>> features;
        vector<double> targets;
    };

    class CsvLoader {
        public:
        static Dataset load(const string& filepath, 
            bool has_header = true);
    };

}

#endif