#include <iostream>
#include <iomanip>
#include "poly_reg/csv_loader.hpp"
#include "poly_reg/preprocessing.hpp"
#include "poly_reg/polynomial_regression.hpp"

int main()
{
    try
    {
        std::cout << "==================================================\n";
        std::cout << " Group 15 Preprocessing & CSV Export Demo         \n";
        std::cout << "==================================================\n\n";

        std::string dataset_path = "data/input/quadratic_clean.csv";
        std::cout << "[INFO] Loading dataset from: " << dataset_path << "\n";
        PolyReg::Matrix raw_dataset = PolyReg::CSVLoader::load_dataset_from_csv(dataset_path);

        int total_rows = raw_dataset.get_rows();
        PolyReg::Matrix X_features(total_rows, 1);
        PolyReg::Matrix y_targets(total_rows, 1);
        for (int r = 0; r < total_rows; ++r)
        {
            X_features.at(r, 0) = raw_dataset.at(r, 0);
            y_targets.at(r, 0) = raw_dataset.at(r, 1);
        }

        // Apply Min-Max Scaling via Tatiana's module
        std::cout << "[INFO] Applying Min-Max Feature Scaling...\n";
        PolyReg::Matrix scaled_X = PolyReg::Preprocessing::compute_min_max_scaling(X_features);

        // Train model
        int degree = 2;
        std::cout << "[INFO] Training OLS model on scaled features (Degree " << degree << ")...\n";
        PolyReg::PolynomialRegression model(degree);
        model.fit(scaled_X, y_targets);

        PolyReg::Matrix predictions = model.predict(scaled_X);
        double rmse = model.calculate_rmse(y_targets, predictions);
        std::cout << "[SUCCESS] Model trained! RMSE: " << std::fixed << std::setprecision(4) << rmse << "\n";

        // Export predictions using Pruna's CSV exporter
        std::string output_path = "data/output/predictions_demo.csv";
        std::cout << "[INFO] Exporting predictions to " << output_path << "...\n";
        PolyReg::CSVLoader::export_predictions_to_csv(output_path, y_targets, predictions);
        std::cout << "[SUCCESS] Predictions successfully exported to disk!\n";
    }
    catch (const std::exception &error)
    {
        std::cerr << "[ERROR] Demo failed: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}