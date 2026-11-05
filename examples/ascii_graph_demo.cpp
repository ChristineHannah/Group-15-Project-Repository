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
        std::string dataset_path = "data/input/degree5_quintic.csv";                           // stores the file path string pointing to Allan's sample dataset file.
        std::cout << "[INFO] Loading dataset from: " << dataset_path << "\n";                  // prints an informational status message to the terminal
        PolyReg::Matrix raw_dataset = PolyReg::CSVLoader::load_dataset_from_csv(dataset_path); // calls Pruna's CSV loader module to open the file
        // and parse the numbers row by row into  a 2D Matrix object.

        int total_rows = raw_dataset.get_rows();   // counts how many rows of data points were loaded from the file
        PolyReg::Matrix X_features(total_rows, 1); // a matrix to holdinout features with a col count of 1
        PolyReg::Matrix y_targets(total_rows, 1);  // matrix to hold target answers with a col count of 1

        double min_x = 1e9, max_x = -1e9; // tracks the lowest and highest X value in the dataset
        // such extreme values ensure that the very first real data point will successfully overwrite it.
        double min_y = 1e9, max_y = -1e9; // lowest and highest Y value in the dataset.

        for (int r = 0; r < total_rows; ++r)
        {
            double xv = raw_dataset.at(r, 0); // .at(r,c) looks inside a grid table
            // col 0 is always reserved for input feature X values
            // col 1 is always reserved for the atarget answer Y values
            double yv = raw_dataset.at(r, 1);
            X_features.at(r, 0) = xv; // copies X value from raw dataset neatly into the separate X features matrix
            y_targets.at(r, 0) = yv;

            if (xv < min_x) // comparison with current minimums and maximus such that we know the absolute lowest and highest bounds of the graph
                min_x = xv;
            if (xv > max_x)
                max_x = xv;
            if (yv < min_y)
                min_y = yv;
            if (yv > max_y)
                max_y = yv;
        }

        // 2. Train Degree-2 Polynomial Regression Model
        int degree = 2;                                                                            // sets the polynomial degree to 2
        std::cout << "[INFO] Training Polynomial Regression Model (Degree " << degree << ")...\n"; // prints a status message
        PolyReg::PolynomialRegression model(degree);                                               // creates a regression model object configured for a degree 2 curve
        model.fit(X_features, y_targets);                                                          // trains the model using the data
        // solving normal equations or fitting weights.

        // 3. Generate Predictions
        PolyReg::Matrix predictions = model.predict(X_features);  // asks the trained model to produce y values based on input
        double mse = model.calculate_mse(y_targets, predictions); // calls  mse function from preprocessing to
        // measure how close the model's cuve is to reality.
        std::cout << "[SUCCESS] Model trained successfully! MSE: " << std::fixed << std::setprecision(4) << mse << "\n\n";
        // prints success message and format the final error score on the screen to a precision of 4

        // 4. Render ASCII Terminal Graph (20 rows x 60 columns)
        // defines the height and width of our text based terminal graph
        int grid_rows = 20;
        int grid_cols = 60;
        // builds a 2D character grid filled entirely with empty spaces ' ' acting linke a blank canvas
        // std::vector<char> a single row of text characters - 60 characters side by side.
        // std::vector<std::vector<char>> a list of lists - a stack of 20 of those rows ontop of each other.
        // grid_rows tells outer list to create 20 rows
        // std::vector... telss each of those 20 rows to hold 60 character slots
        std::vector<std::vector<char>> grid(grid_rows, std::vector<char>(grid_cols, ' '));

        // Populate grid with model estimation curve points ('+') and actual data ('*')
        for (int r = 0; r < grid_rows; ++r)
        { // nested for loops that walks through the outer edgess of the grid and draws border lines
          // putting dashes - across the top and botton
          // vertical bars | down the left and right sides.
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
        { // loops through every original data point from the file
            double xv = X_features.at(i, 0);
            double yv = y_targets.at(i, 0);

            int c = static_cast<int>((xv - min_x) / (max_x - min_x) * (grid_cols - 4)) + 2; // gives a column number between 1 and 58 to be plotted
            int r = grid_rows - 1 - static_cast<int>((yv - min_y) / (max_y - min_y) * (grid_rows - 4)) - 2;
            // computer screens count rows from top to bottom where row 20 is the floor
            // calculates the percentage of high up the Y value is eg if Y =246
            // scales it down to the 20 row screen height
            // subtracts it from total rows to flip the graph right side up up so low numbers stay at the bottom and high numbers go to the top
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