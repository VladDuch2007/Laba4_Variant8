#pragma once

#if defined(ANOMALY_EXPORTS)
#define ANOMALY_API extern "C" __declspec(dllexport)
#elif defined(ANOMALY_IMPORTS)
#define ANOMALY_API extern "C" __declspec(dllimport)
#else
#define ANOMALY_API extern "C"
#endif

ANOMALY_API double zScore(
    const double* data,
    int count,
    int index
);

ANOMALY_API int iqrOutliers(
    const double* data,
    int count,
    int* flags
);

ANOMALY_API int detectOutliers(
    const double* data,
    int count,
    double threshold,
    int* flags
);

ANOMALY_API double anomalyRate(
    const int* flags,
    int count
);