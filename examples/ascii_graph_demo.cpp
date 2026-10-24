#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "poly_reg/csv_loader.hpp"
#include "poly_reg/polynomial_regression.hpp"

int main()
{
    try
    {
        std::cout << "==================================================\n";
        std::cout << " Group 15 ASCII Polynomial Regression Graph Demo  \n";
        std::cout << "==================================================\n\n";

        // 1. Load Dataset
        std::string dataset_path = "data/input/quadratic_clean.csv";
        std::cout << "[INFO] Loading dataset from: " << dataset_path << "\n";
        PolyReg::Matrix raw_dataset = PolyReg::CSVLoader::load_dataset_from_csv(dataset_path);

        int total_rows = raw_dataset.get_rows();
        PolyReg::Matrix X_features(total_rows, 1);
        PolyReg::Matrix y_targets(total_rows, 1);

        double min_x = 1e9, max_x = -1e9;
        double min_y = 1e9, max_y = -1e9;

        for (int r = 0; r < total_rows; ++r)
        {
            double xv = raw_dataset.at(r, 0);
            double yv = raw_dataset.at(r, 1);
            X_features.at(r, 0) = xv;
            y_targets.at(r, 0) = yv;

            if (xv < min_x)
                min_x = xv;
            if (xv > max_x)
                max_x = xv;
            if (yv < min_y)
                min_y = yv;
            if (yv > max_y)
                max_y = yv;
        }

        // 2. Train Degree-2 Polynomial Regression Model
        int degree = 2;
        std::cout << "[INFO] Training Polynomial Regression Model (Degree " << degree << ")...\n";
        PolyReg::PolynomialRegression model(degree);
        model.fit(X_features, y_targets);

        // 3. Generate Predictions
        PolyReg::Matrix predictions = model.predict(X_features);
        double mse = model.calculate_mse(y_targets, predictions);
        std::cout << "[SUCCESS] Model trained successfully! MSE: " << std::fixed << std::setprecision(4) << mse << "\n\n";

        // 4. Render ASCII Terminal Graph (20 rows x 60 columns)
        int grid_rows = 20;
        int grid_cols = 60;
        std::vector<std::vector<char>> grid(grid_rows, std::vector<char>(grid_cols, ' '));

        // Populate grid with model estimation curve points ('+') and actual data ('*')
        for (int r = 0; r < grid_rows; ++r)
        {
            for (int c = 0; c < grid_cols; ++c)
            {
                // Border lines
                if (r == 0 || r == grid_rows - 1)
                    grid[r][c] = '-';
                else if (c == 0 || c == grid_cols - 1)
                    grid[r][c] = '|';
            }
        }

        // Plot actual data points as '*'
        for (int i = 0; i < total_rows; ++i)
        {
            double xv = X_features.at(i, 0);
            double yv = y_targets.at(i, 0);

            int c = static_cast<int>((xv - min_x) / (max_x - min_x) * (grid_cols - 4)) + 2;
            int r = grid_rows - 1 - static_cast<int>((yv - min_y) / (max_y - min_y) * (grid_rows - 4)) - 2;

            if (r >= 1 && r < grid_rows - 1 && c >= 1 && c < grid_cols - 1)
            {
                grid[r][c] = '*';
            }
        }

        // Plot fitted estimation curve sampled across columns as '+'
        for (int c_idx = 1; c_idx < grid_cols - 1; ++c_idx)
        {
            double norm_x = static_cast<double>(c_idx - 2) / (grid_cols - 4);
            double xv = min_x + norm_x * (max_x - min_x);

            PolyReg::Matrix single_pt(1, 1, xv);
            PolyReg::Matrix pred_pt = model.predict(single_pt);
            double yv = pred_pt.at(0, 0);

            int r = grid_rows - 1 - static_cast<int>((yv - min_y) / (max_y - min_y) * (grid_rows - 4)) - 2;
            if (r >= 1 && r < grid_rows - 1 && c_idx >= 1 && c_idx < grid_cols - 1)
            {
                if (grid[r][c_idx] == ' ')
                {
                    grid[r][c_idx] = '+';
                }
            }
        }

        // Print Graph Output to Console
        std::cout << "--- VISUAL ESTIMATION GRAPH (* = Actual Data, + = Model Curve) ---\n";
        std::cout << "Y-Max (" << std::fixed << std::setprecision(1) << max_y << ")\n";
        for (int r = 0; r < grid_rows; ++r)
        {
            std::cout << " ";
            for (int c = 0; c < grid_cols; ++c)
            {
                std::cout << grid[r][c];
            }
            std::cout << "\n";
        }
        std::cout << "Y-Min (" << min_y << ")                                     X-Max (" << max_x << ")\n";
        std::cout << "------------------------------------------------------------------\n";
    }
    catch (const std::exception &error)
    {
        std::cerr << "[ERROR] Graph demo failed: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}