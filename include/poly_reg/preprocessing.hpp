//this tells the computer to only read this file once during compiling so do not get confused by duplicate definitions

#pragma once

#include <vector>
#include <utility>
#include "matrix.hpp" //this brings in Kasule's matrix class

namespace poly_reg{
    //Standardization
    //this will take a reference to the matrix and scale its values
    void Standardize (Matrix& data);

    //Min-Max Scaling
    //this scale sthe matrix features into a specific range
    void MinmaxScale (Matrix& data, double min_val = 0.0, double max_val = 1.0);

    //Train/Test Split
    //this splits a dataset matrix into training and testing subsets
    std::pair <Matrix, Matrix> TraintestSplit (const Matrix& data, double train_ratio = 0.8);

}