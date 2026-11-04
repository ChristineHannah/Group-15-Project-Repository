#pragma once
#include "poly_reg/matrix.hpp" // this imports the matrix class header

namespace PolyReg // wraps all code inside the project's global namespace to avoid naming collisions with external C++ library
{
    class PolynomialRegression
    {
    private:
        int polynomial_degree;      // a private variable for the degree of the polynomial model
        Matrix weight_coefficients; // a container that holds the solved regression weights )beta) after the model is trained via OLS or gradient descent.
    public:
        // explicit keyword stops the compiler from converting a raw integer into a polynomialregression object automatically.
        // eg trainModel(3) wouldn't compile because 3 is an integer not a polynomialregression model.
        explicit PolynomialRegression(int degree = 1); // the class constructor - sets a degree of 1 if none is provided.

        // Base Matrix Product Methods (OLS Formulations)
        Matrix compute_normal_matrix_product(const Matrix &design_matrix) const; // computes the normal equation matrix product (X^T*X) in the normal equation.
        // const promises that the function will not modify the object's internal data.
        Matrix compute_normal_vector_product(const Matrix &design_matrix, const Matrix &target_vector) const; // computes the normal equation vector product (X^-1 * y)

        // Gradient Descent Cost & Gradient Helpers
        Matrix compute_cost_gradient(const Matrix &design_matrix, const Matrix &target_vector, const Matrix &predictions) const; // a function that calculates the error gradient vector across predictions
        // calculates the gradient vector to find out which direction has more errors and which one has less
        // calculates both the size of the mistake and who is responsible.
        // tells the model which direction and how steeply to adjust its weights during iterative training

        double compute_total_cost(const Matrix &target_vector, const Matrix &predictions) const; // function that calculates the total error by comparing true targets against model predictions

        // Model Fitting Solvers (OLS Normal Equations & Gradient Descent)
        void fit(const Matrix &input_features, const Matrix &target_values); // declares the main training function for OLS equations.
        // takes input features and target values and saves the resulting weights (beta)

        void fit_gradient_descent(const Matrix &input_features, const Matrix &target_values, double learning_rate, int epochs); // function tells the computer to train the model by practicing over and over again.
        // a function for training the model using gradient descent.

        Matrix predict(const Matrix &input_features) const; // a function to enable the model make future predictions on new data
        // takes new input features, expands them into polynomial degress.
        // multiplies them by learned weights (beta) and returns predicted target values.

        // Computes the Mean Squared Error (MSE) between true targets and predictions.
        // Grades how accurate the model's curve fit is.
        // the lower the mse, the more accurate the model is.
        double calculate_mse(const Matrix &y_true, const Matrix &y_pred) const;

        // Computes the Root Mean Squared ERROR (RMSE) by taking the square root of MSE.
        // MSE since it squares, distorts units from eg metres to square metres.
        // rmse takes the root of the mse such that the units go back to metres
        // such that it is easier to say things like ' predictions are off by 1.5 metres'
        double calculate_rmse(const Matrix &y_true, const Matrix &y_pred) const;

        // Convergence Loss Tracker
        // Evaluates final model convergence loss using MSE on input features and targets.
        // Asks the question ' Did the model finish learning successfully'
        // takes input data and true answers, runs a prediction test and calculates the final MSE to see how much the model learned/ converged after all the training loops.
        // if output is too high or is not a number (NaN) - indication that something went wrong during training
        double calculate_final_convergence_loss(const Matrix &X_input, const Matrix &y_target) const;

        // Getters
        // Returns the polynomial degree configured for this model.
        int get_degree() const; // read only getter function

        // Returs the trained weight coefficients matrix.
        // read only getter function to return the tained weight matrix (beta)
        Matrix get_coefficients() const;
    };
} // namespace PolyReg