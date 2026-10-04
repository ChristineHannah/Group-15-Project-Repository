#include "poly_reg/preprocessing.hpp"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace poly_reg {
    // 1.Standardization function
    void Standardize(Matrix& data){
        size_t rows = data.rows();
        size_t cols = data.cols();

        if (rows == 0  | | cols ==0) 
        return;
        //scale each column by column
        for (size_t j = 0; j < cols; ++j){
            double sum = 0.0;
            for (size_t i = 0; i < rows; ++i){
                sum += data (i,j);
            }
            double mean = sum / rows;

            double variance_sum = 0.0;
            for (size_t i = 0; i < rows; ++i){
                variance_sum += std::pow(data(i,j) - mean, 2);
            }
           double std_dev = std::sqrt(variance_sum / rows);
           
           //avoid division by zero
           if (std_dev == 0.0)
           continue;

           for (size_t i = 0; i < rows; ++i){
            data (i, j) = (data(i,j) - mean) / std_dev;
           }
        }
    }
    //2. Min-max scaling function
    void MinmaxScale(Matrix& data, double min_val, double max_value){
        size_t rows = data.rows();
        size_t cols = data.cols();

        if (rows == 0  | | cols == 0)
        return;

        for (size_t j = 0; j < cols; ++j){
            double col_min = data (0,j);
            double col_max = data (0,j);

            //find min and max for the current column
            for (size_t i = 1; i < rows; ++i){
                if (data(i,j) < col_min) col_min = data(i,j);
                if (data(i,j) > col_max) col_max = data(i,j);
            
            }
            double range = col_max - col_min;

            // scale column values
            for (size_t i = 0; i < rows; ++i){
                if (range == 0.0){
                    data(i,j) = min_val;
                
                }
                else {
                    double normalized = (data(i,j) - col_min) / range;
                    data(i, j) = normalized * (max_val - min_val) + min_val;
                }
            }

        }
    }

    //3. Train-test split function
    std::pair <Matrix, Matrix> TraintestSplit(const Matrix& data, double train_ratio)
    size_t total_rows = data.rows();
    size_t train_rows = static_cast<size_t> (total_rows * train_ratio);
    size_t test_rows = total_rows - train_rows;

    //assume the matrix class has aconstructor like Matrix(rows, columns)
    Matrix train_data (train_rows, data.cols());
    Matrix test_data (test_rows, data.cols());

    // copy data into train subset
    for (size_t i = 0; i < train_rows; ++i){
        for (size_t j = 0; j < data.cols(); ++j){
            train_data(i,j) = data(i,j);
        }
    }

    // copy remaining data into testing subset
    for (size_t i = 0; i < test_rows; ++i){
        for (size_t j = 0; j < data.cols(); ++j){
            test_data(i,j) = data(train_rows + i, j);
        }
    }
    return {train_data, test_data};
}