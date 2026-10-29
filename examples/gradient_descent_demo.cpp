#include <iostream>
#include <iomanip>
#include "poly_reg/csv_loader.hpp"
#include "poly_reg/polynomial_regression.hpp"

int main()
{
    try
    {
        std::cout << "========================================\n";
        std::cout << " Group 15 Gradient Descent Optimizer Demo \n";
        std::cout << "========================================\n\n";

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

        int degree = 2;
        double learning_rate = 0.01;
        int epochs = 2000;
        std::cout << "[INFO] Training via Gradient Descent (Degree " << degree << ", LR: " << learning_rate << ", Epochs: " << epochs << ")...\n";

        PolyReg::PolynomialRegression gd_model(degree);
        gd_model.fit_gradient_descent(X_features, y_targets, learning_rate, epochs);

        PolyReg::Matrix weights = gd_model.get_coefficients();
        std::cout << "\n[SUCCESS] Gradient Descent Learned Weights (Beta):\n";
        for (int r = 0; r < weights.get_rows(); ++r)
        {
            std::cout << " Beta[" << r << "] = " << std::fixed << std::setprecision(4) << weights.at(r, 0) << "\n";
        }

        PolyReg::Matrix predictions = gd_model.predict(X_features);
        double mse = gd_model.calculate_mse(y_targets, predictions);
        std::cout << "\n[EVALUATION] Final Convergence MSE: " << std::fixed << std::setprecision(6) << mse << "\n";
        std::cout << "[INFO] Gradient Descent Demo executed successfully!\n";
    }
    catch (const std::exception &error)
    {
        std::cerr << "[ERROR] Demo failed: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}