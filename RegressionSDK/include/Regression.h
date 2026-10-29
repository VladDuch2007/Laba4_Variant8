#pragma once

#if defined(REGRESSION_EXPORTS)
#define REGRESSION_API extern "C" __declspec(dllexport)
#elif defined(REGRESSION_IMPORTS)
#define REGRESSION_API extern "C" __declspec(dllimport)
#else
#define REGRESSION_API extern "C"
#endif

REGRESSION_API int linearRegression(
    const double* x,
    const double* y,
    int count,
    double* slope,
    double* intercept
);

REGRESSION_API double predict(
    double slope,
    double intercept,
    double x
);

REGRESSION_API double rSquared(
    const double* x,
    const double* y,
    int count,
    double slope,
    double intercept
);

REGRESSION_API int residuals(
    const double* x,
    const double* y,
    int count,
    double slope,
    double intercept,
    double* result
);
