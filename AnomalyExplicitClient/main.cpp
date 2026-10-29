
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <cmath>

using ZScoreFunc = double (*)(
    const double*, int, int
);

using IQRFunc = int (*)(
    const double*, int, int*
);

using DetectFunc = int (*)(
    const double*, int, double, int*
);

using RateFunc = double (*)(
    const int*, int
);

int main() {
    HMODULE library = LoadLibraryW(L"AnomalyLib.dll");

    if (!library) {
        std::cerr << "DLL loading failed\n";
        return 1;
    }

    auto zScore = reinterpret_cast<ZScoreFunc>(
        GetProcAddress(library, "zScore")
    );

    auto iqrOutliers = reinterpret_cast<IQRFunc>(
        GetProcAddress(library, "iqrOutliers")
    );

    auto detectOutliers = reinterpret_cast<DetectFunc>(
        GetProcAddress(library, "detectOutliers")
    );

    auto anomalyRate = reinterpret_cast<RateFunc>(
        GetProcAddress(library, "anomalyRate")
    );

    if (!zScore || !iqrOutliers ||
        !detectOutliers || !anomalyRate) {
        std::cerr << "DLL function not found\n";
        FreeLibrary(library);
        return 1;
    }

    const double data[] = {
        10, 11, 12, 10, 13, 11, 100
    };

    const int count = 7;
    int iqrFlags[count] = {};
    int zFlags[count] = {};

    if (!iqrOutliers(data, count, iqrFlags) ||
        !detectOutliers(data, count, 2.0, zFlags)) {
        FreeLibrary(library);
        return 1;
    }

    std::cout << std::fixed
              << std::setprecision(2);

    std::cout << "Explicit DLL Linking\n";

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

    FreeLibrary(library);
    return 0;
}
