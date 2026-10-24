#include <iostream>
#include <iomanip>
#include "poly_reg/csv_loader.hpp"
#include "poly_reg/preprocessing.hpp"
#include "poly_reg/polynomial_regression.hpp"

int main() {
    try {
        std::cout << "===========================================\n";
        std::cout << "   Group 15 Polynomial Regression Demo     \n";
        std::cout << "===========================================\n\n";

        // 1. Load Dataset
        std::string dataset_path = "data/input/quadratic_clean.csv";
        std::cout << "[INFO] Loading dataset from: " << dataset_path << "\n";
        Matrix raw_dataset = PolyReg::CSVLoader::load_dataset_from_csv(dataset_path);

        // Separate Features (Col 0) and Target (Col 1)
        int total_rows = raw_dataset.get_rows();
        PolyReg::Matrix X_features(total_rows, 1);
        PolyReg::Matrix y_targets(total_rows, 1);

        for (int r = 0; r < total_rows; ++r) {
            X_features.at(r, 0) = raw_dataset.at(r, 0);
            y_targets.at(r, 0) = raw_dataset.at(r, 1);
        }

        // 2. Train Degree-2 Polynomial Regression Model
        int degree = 2;
        std::cout << "[INFO] Fitting Polynomial Regression Model (Degree " << degree << ")...\n";
        PolyReg::PolynomialRegression model(degree);
        model.fit(X_features, y_targets);

        // 3. Output Learned Weights
        PolyReg::Matrix weights = model.get_coefficients();
        std::cout << "\n[SUCCESS] Learned Weight Vector (Beta):\n";
        for (int r = 0; r < weights.get_rows(); ++r) {
            std::cout << "  Beta[" << r << "] = " << std::fixed << std::setprecision(4) << weights.at(r, 0) << "\n";
        }

        // 4. Generate Predictions
        PolyReg::Matrix predictions = model.predict(X_features);
        double mse = PolyReg::RegressionMetrics::compute_mean_squared_error(y_targets, predictions);
        double rmse = PolyReg::RegressionMetrics::compute_root_mean_squared_error(y_targets, predictions);

        std::cout << "\n[EVALUATION METRICS]\n";
        std::cout << "  Mean Squared Error (MSE) : " << mse << "\n";
        std::cout << "  Root Mean Sq. Error (RMSE): " << rmse << "\n";

    } catch (const std::exception& error) {
        std::cerr << "[ERROR] Execution failed: " << error.what() << std::endl;
        return 1;
    }

    return 0;
}