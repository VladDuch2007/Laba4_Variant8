#include "Regression.h"
#include <cmath>
#include <limits>

namespace {

bool validData(const double* x, const double* y, int count) {
    if (!x || !y || count < 2)
        return false;

    for (int i = 0; i < count; i++) {
        if (!std::isfinite(x[i]) || !std::isfinite(y[i]))
            return false;
    }

    return true;
}

double invalidResult() {
    return std::numeric_limits<double>::quiet_NaN();
}

}

int linearRegression(
    const double* x,
    const double* y,
    int count,
    double* slope,
    double* intercept
) {
    if (!validData(x, y, count) || !slope || !intercept)
        return 0;

    double meanX = 0.0;
    double meanY = 0.0;

    for (int i = 0; i < count; i++) {
        meanX += x[i];
        meanY += y[i];
    }

    meanX /= count;
    meanY /= count;

    double numerator = 0.0;
    double denominator = 0.0;

    for (int i = 0; i < count; i++) {
        double dx = x[i] - meanX;
        double dy = y[i] - meanY;

        numerator += dx * dy;
        denominator += dx * dx;
    }

    if (denominator <= 0.0 || !std::isfinite(denominator))
        return 0;

    double a = numerator / denominator;
    double b = meanY - a * meanX;

    if (!std::isfinite(a) || !std::isfinite(b))
        return 0;

    *slope = a;
    *intercept = b;

    return 1;
}

double predict(
    double slope,
    double intercept,
    double x
) {
    if (!std::isfinite(slope) ||
        !std::isfinite(intercept) ||
        !std::isfinite(x))
        return invalidResult();

    double result = slope * x + intercept;

    if (!std::isfinite(result))
        return invalidResult();

    return result;
}

double rSquared(
    const double* x,
    const double* y,
    int count,
    double slope,
    double intercept
) {
    if (!validData(x, y, count) ||
        !std::isfinite(slope) ||
        !std::isfinite(intercept))
        return invalidResult();

    double meanY = 0.0;

    for (int i = 0; i < count; i++)
        meanY += y[i];

    meanY /= count;

    double ssTotal = 0.0;
    double ssResidual = 0.0;

    for (int i = 0; i < count; i++) {
        double predicted = predict(slope, intercept, x[i]);

        if (!std::isfinite(predicted))
            return invalidResult();

        double diff = y[i] - meanY;
        double error = y[i] - predicted;

        ssTotal += diff * diff;
        ssResidual += error * error;
    }

    if (!std::isfinite(ssTotal) ||
        !std::isfinite(ssResidual))
        return invalidResult();

    if (ssTotal == 0.0)
        return ssResidual == 0.0 ? 1.0 : 0.0;

    return 1.0 - ssResidual / ssTotal;
}

int residuals(
    const double* x,
    const double* y,
    int count,
    double slope,
    double intercept,
    double* result
) {
    if (!validData(x, y, count) || !result ||
        !std::isfinite(slope) ||
        !std::isfinite(intercept))
        return 0;

    for (int i = 0; i < count; i++) {
        double predicted = predict(slope, intercept, x[i]);

        if (!std::isfinite(predicted))
            return 0;

        double error = y[i] - predicted;

        if (!std::isfinite(error))
            return 0;

        result[i] = error;
    }

    return 1;
}