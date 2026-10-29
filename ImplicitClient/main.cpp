#include <iostream>
#include <iomanip>
#include "Regression.h"

int main() {
    const double x[] = { 1, 2, 3, 4, 5 };
    const double y[] = { 5, 8, 11, 14, 17 };

    double slope = 0.0;
    double intercept = 0.0;
    double errors[5] = {};

    if (!linearRegression(x, y, 5, &slope, &intercept)) {
        return 1;
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Implicit DLL Linking\n";
    std::cout << "Slope: " << slope << "\n";
    std::cout << "Intercept: " << intercept << "\n";
    std::cout << "Prediction: "
              << predict(slope, intercept, 6) << "\n";
    std::cout << "R-squared: "
              << rSquared(x, y, 5, slope, intercept)
              << "\n";

    if (!residuals(x, y, 5, slope, intercept, errors)) {
        return 1;
    }

    std::cout << "Residuals: ";
    for (double value : errors) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return 0;
}