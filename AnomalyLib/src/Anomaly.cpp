#include "Anomaly.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

namespace {

double invalidValue() {
    return std::numeric_limits<double>::quiet_NaN();
}

bool calculateStats(
    const double* data,
    int count,
    double& mean,
    double& deviation
) {
    if (!data || count < 2)
        return false;

    double sum = 0.0;

    for (int i = 0; i < count; ++i) {
        if (!std::isfinite(data[i]))
            return false;

        sum += data[i];
    }

    mean = sum / count;

    if (!std::isfinite(mean))
        return false;

    double variance = 0.0;

    for (int i = 0; i < count; ++i) {
        double difference = data[i] - mean;
        variance += difference * difference;
    }

    variance /= count;

    if (!std::isfinite(variance))
        return false;

    deviation = std::sqrt(variance);
    return std::isfinite(deviation);
}

double median(
    const std::vector<double>& values,
    int first,
    int last
) {
    int size = last - first;

    if (size % 2 == 1)
        return values[first + size / 2];

    double a = values[first + size / 2 - 1];
    double b = values[first + size / 2];

    return a / 2.0 + b / 2.0;
}

}

double zScore(
    const double* data,
    int count,
    int index
) {
    if (index < 0 || index >= count)
        return invalidValue();

    double mean;
    double deviation;

    if (!calculateStats(data, count, mean, deviation))
        return invalidValue();

    if (deviation == 0.0)
        return invalidValue();

    double result = (data[index] - mean) / deviation;

    return std::isfinite(result)
        ? result
        : invalidValue();
}

int iqrOutliers(
    const double* data,
    int count,
    int* flags
) {
    if (!data || !flags || count < 4)
        return 0;

    std::vector<double> sorted;

    for (int i = 0; i < count; ++i) {
        if (!std::isfinite(data[i]))
            return 0;

        sorted.push_back(data[i]);
    }

    std::sort(sorted.begin(), sorted.end());

    int half = count / 2;

    double q1 = median(sorted, 0, half);
    double q3 = median(
        sorted,
        count % 2 == 0 ? half : half + 1,
        count
    );

    double iqr = q3 - q1;
    double lower = q1 - 1.5 * iqr;
    double upper = q3 + 1.5 * iqr;

    if (!std::isfinite(lower) ||
        !std::isfinite(upper))
        return 0;

    for (int i = 0; i < count; ++i) {
        flags[i] = (data[i] < lower || data[i] > upper)
            ? 1 : 0;
    }

    return 1;
}

int detectOutliers(
    const double* data,
    int count,
    double threshold,
    int* flags
) {
    if (!flags || !std::isfinite(threshold) ||
        threshold <= 0.0)
        return 0;

    double mean;
    double deviation;

    if (!calculateStats(data, count, mean, deviation))
        return 0;

    for (int i = 0; i < count; ++i) {
        if (deviation == 0.0) {
            flags[i] = 0;
        }
        else {
            double score = (data[i] - mean) / deviation;

            if (!std::isfinite(score))
                return 0;

            flags[i] = std::abs(score) > threshold
                ? 1 : 0;
        }
    }

    return 1;
}

double anomalyRate(
    const int* flags,
    int count
) {
    if (!flags || count <= 0)
        return invalidValue();

    int anomalies = 0;

    for (int i = 0; i < count; ++i) {
        if (flags[i] != 0 && flags[i] != 1)
            return invalidValue();

        anomalies += flags[i];
    }

    return static_cast<double>(anomalies) / count;
}