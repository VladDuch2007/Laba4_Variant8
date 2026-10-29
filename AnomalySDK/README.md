# Anomaly Detection Library SDK

Version: 1.0
Variant: 8
Module: Anomaly Detection

## Description

AnomalyLib is a C++ library for detecting
outliers in numerical data.

## Platform

Windows x64
C++20
CMake 3.20 or newer

## Files

include/Anomaly.h
lib/AnomalyLib.lib
bin/AnomalyLib.dll

## API Contract

### zScore()

double zScore(
    const double* data,
    int count,
    int index
);

Calculates the Z-score of the element
at the specified index.

Uses population standard deviation.

Requirements:
- data must not be nullptr.
- count must be at least 2.
- index must be within the array.
- All values must be finite.
- Standard deviation must not be zero.

Returns:
- Calculated Z-score on success.
- NaN for invalid input.

### iqrOutliers()

int iqrOutliers(
    const double* data,
    int count,
    int* flags
);

Detects outliers using the IQR method.

Requirements:
- Valid data and flags pointers.
- At least 4 elements.
- All data values must be finite.
- flags must have space for count integers.

The sorted data is divided into lower
and upper halves. For odd counts, the
middle value is excluded.

An outlier is outside:
[Q1 - 1.5 * IQR, Q3 + 1.5 * IQR]

Returns:
1 - success.
0 - failure.

Output:
1 - outlier.
0 - normal value.

### detectOutliers()

int detectOutliers(
    const double* data,
    int count,
    double threshold,
    int* flags
);

Detects anomalies using Z-scores.

Requirements:
- count must be at least 2.
- All input values must be finite.
- threshold must be finite and > 0.
- Pointers must be valid.
- flags must hold count integers.

An anomaly is detected when:
abs(Z-score) > threshold.

For constant data, all flags are zero.

Returns:
1 - success.
0 - failure.

### anomalyRate()

double anomalyRate(
    const int* flags,
    int count
);

Calculates the proportion of anomalies.

Requirements:
- flags must not be nullptr.
- count must be greater than zero.
- Every flag must be 0 or 1.

Formula:
anomalyRate = anomalyCount / count

Returns:
- Value from 0 to 1 on success.
- NaN for invalid input.

## Error Handling

Invalid pointers and invalid values
are checked before calculations.

The caller owns the input arrays
and output buffers.

No caller-owned memory is freed
by the library.

On calculation failure, output
buffers are not guaranteed to remain
unchanged.

## Linking

Implicit linking requires:
- Anomaly.h
- AnomalyLib.lib
- AnomalyLib.dll

Define ANOMALY_IMPORTS in the client.

Explicit linking requires:
- AnomalyLib.dll

Use:
LoadLibrary()
GetProcAddress()
FreeLibrary()

Exported functions use C linkage.

## Example

Input:
10, 11, 12, 10, 13, 11, 100

Expected:
Z-score of 100: approximately 2.45
IQR flags: 0 0 0 0 0 0 1
Z-score flags (threshold 2): 0 0 0 0 0 0 1
Anomaly rate: approximately 0.14

## Compatibility

Windows x64 applications.
API version: 1.0