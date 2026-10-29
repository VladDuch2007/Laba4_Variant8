#include <iostream>
#include <iomanip>
#include "Regression.h"

int main() {
    const double x[] = { 1, 2, 3, 4, 5 };
    const double y[] = { 5, 8, 11, 14, 17 };
    const int count = 5;

    double slope = 0.0;
    double intercept = 0.0;

    int status = linearRegression(
        x, y, count, &slope, &intercept
    );

    if (status == 0) {
        return 1;
    }

    std::cout << std::fixed
              << std::setprecision(2);

    std::cout << "Slope: " << slope << "\n";
    std::cout << "Intercept: " << intercept << "\n";

    double prediction = predict(
        slope, intercept, 6.0
    );

    std::cout << "Prediction for x=6: "
              << prediction << "\n";

    double r2 = rSquared(
        x, y, count, slope, intercept
    );

    std::cout << "R-squared: " << r2 << "\n";

    double errors[count] = {};

    int residualStatus = residuals(
        x, y, count,
        slope, intercept, errors
    );

    if (residualStatus == 0) {
        return 1;
    }

    std::cout << "Residuals: ";

    for (int i = 0; i < count; i++) {
        std::cout << errors[i] << " ";
    }

    std::cout << "\n";

    const double sameX[] = { 2, 2, 2 };
    const double testY[] = { 1, 2, 3 };

    int invalidStatus = linearRegression(
        sameX, testY, 3, &slope, &intercept
    );

    std::cout << "Constant X status: "
              << invalidStatus << "\n";

    int nullStatus = linearRegression(
        nullptr, y, count,
        &slope, &intercept
    );

    std::cout << "Null data status: "
              << nullStatus << "\n";

    return 0;
}