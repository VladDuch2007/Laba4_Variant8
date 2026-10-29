
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Anomaly.h"

int main() {
    const double data[] = {
        10, 11, 12, 10, 13, 11, 100
    };

    const int count = 7;
    int iqrFlags[count] = {};
    int zFlags[count] = {};

    if (!iqrOutliers(data, count, iqrFlags))
        return 1;

    if (!detectOutliers(data, count, 2.0, zFlags))
        return 1;

    std::cout << std::fixed
              << std::setprecision(2);

    std::cout << "Implicit DLL Linking\n";

    std::cout << "Z-score: "
              << zScore(data, count, 6) << "\n";

    std::cout << "IQR flags: ";
    for (int flag : iqrFlags)
        std::cout << flag << " ";

    std::cout << "\nZ-score flags: ";
    for (int flag : zFlags)
        std::cout << flag << " ";

    std::cout << "\nAnomaly rate: "
              << anomalyRate(zFlags, count) << "\n";

    std::cout << "Null pointer handled: "
              << std::isnan(zScore(nullptr, count, 0))
              << "\n";

    std::cout << "Small array handled: "
              << (iqrOutliers(data, 3, iqrFlags) == 0)
              << "\n";

    std::cout << "Invalid threshold handled: "
              << (detectOutliers(data, count, 0.0, zFlags) == 0)
              << "\n";

    return 0;
}
