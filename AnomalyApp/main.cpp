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

    std::cout << std::fixed
              << std::setprecision(2);

    std::cout << "Z-score: "
              << zScore(data, count, 6) << "\n";

    if (!iqrOutliers(data, count, iqrFlags))
        return 1;

    std::cout << "IQR outliers: ";

    for (int value : iqrFlags)
        std::cout << value << " ";

    std::cout << "\n";

    if (!detectOutliers(data, count, 2.0, zFlags))
        return 1;

    std::cout << "Detected outliers: ";

    for (int value : zFlags)
        std::cout << value << " ";

    std::cout << "\n";

    std::cout << "Anomaly rate: "
              << anomalyRate(zFlags, count) << "\n";

    std::cout << "Null input rejected: "
              << std::isnan(
                  zScore(nullptr, count, 0)
              ) << "\n";

    return 0;
}