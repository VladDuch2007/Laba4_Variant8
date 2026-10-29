#include <windows.h>
#include <iostream>
#include <iomanip>

using LinearRegressionFunc = int (*)(
    const double*, const double*, int, double*, double*
);

using PredictFunc = double (*)(double, double, double);

using RSquaredFunc = double (*)(
    const double*, const double*, int, double, double
);

using ResidualsFunc = int (*)(
    const double*, const double*, int,
    double, double, double*
);

int main() {
    HMODULE library = LoadLibraryW(L"RegressionLib.dll");

    if (!library) {
        std::cerr << "DLL loading failed\n";
        return 1;
    }

    auto linearRegression =
        reinterpret_cast<LinearRegressionFunc>(
            GetProcAddress(library, "linearRegression")
        );

    auto predict =
        reinterpret_cast<PredictFunc>(
            GetProcAddress(library, "predict")
        );

    auto rSquared =
        reinterpret_cast<RSquaredFunc>(
            GetProcAddress(library, "rSquared")
        );

    auto residuals =
        reinterpret_cast<ResidualsFunc>(
            GetProcAddress(library, "residuals")
        );

    if (!linearRegression || !predict ||
        !rSquared || !residuals) {
        std::cerr << "DLL function not found\n";
        FreeLibrary(library);
        return 1;
    }

    const double x[] = { 1, 2, 3, 4, 5 };
    const double y[] = { 5, 8, 11, 14, 17 };

    double slope = 0.0;
    double intercept = 0.0;
    double errors[5] = {};

    if (!linearRegression(x, y, 5, &slope, &intercept)) {
        FreeLibrary(library);
        return 1;
    }

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Explicit DLL Linking\n";
    std::cout << "Slope: " << slope << "\n";
    std::cout << "Intercept: " << intercept << "\n";
    std::cout << "Prediction: "
              << predict(slope, intercept, 6) << "\n";
    std::cout << "R-squared: "
              << rSquared(x, y, 5, slope, intercept)
              << "\n";

    if (!residuals(x, y, 5, slope, intercept, errors)) {
        FreeLibrary(library);
        return 1;
    }

    std::cout << "Residuals: ";
    for (double value : errors) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    FreeLibrary(library);
    return 0;
}