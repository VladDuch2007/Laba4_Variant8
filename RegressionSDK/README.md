# Regression Library SDK

Version: 1.0
Developer: Duchinsky Vladyslav
Group: FIT-3-17
Variant: 8

## Description

RegressionLib is a C++ dynamic library for
simple linear regression analysis.

The library provides four functions:

- linearRegression()
- predict()
- rSquared()
- residuals()

## Platform

Windows x64
C++20
CMake 3.20 or newer

## Package Contents

include/Regression.h
lib/RegressionLib.lib
bin/RegressionLib.dll

## API Contract

### linearRegression

int linearRegression(
    const double* x,
    const double* y,
    int count,
    double* slope,
    double* intercept
);

Calculates linear regression coefficients
for the model y = slope * x + intercept.

Requirements:
- x and y must not be null.
- slope and intercept must not be null.
- count must be at least 2.
- Arrays must contain at least count elements.
- Input values must be finite.
- X values must not all be identical.

Returns:
1 - success.
0 - invalid input or calculation failure.

Output coefficients are written only on success.

### predict

double predict(
    double slope,
    double intercept,
    double x
);

Returns the predicted Y value.

Formula:
y = slope * x + intercept

Returns NaN if an argument or result is
not finite.

### rSquared

double rSquared(
    const double* x,
    const double* y,
    int count,
    double slope,
    double intercept
);

Calculates the coefficient of determination R2.

Requirements:
- Valid input arrays.
- At least 2 observations.
- Finite coefficients.

Returns:
R2 for valid inputs.
NaN for invalid data.

For constant observed Y:
- Returns 1 if predictions are exact.
- Returns 0 otherwise.

R2 can be negative for a poor model.

### residuals

int residuals(
    const double* x,
    const double* y,
    int count,
    double slope,
    double intercept,
    double* result
);

Calculates residual errors.

Formula:
error[i] = y[i] - predicted[i]

Requirements:
- All pointers must be valid.
- Output buffer must hold count doubles.
- count must be at least 2.
- Input values and coefficients must be finite.

Returns:
1 - success.
0 - invalid input or calculation failure.

On failure, output buffer contents are
not guaranteed to remain unchanged.

## Error Handling

The library validates null pointers,
invalid array sizes, non-finite values,
and invalid regression input.

Functions do not allocate or free memory
provided by the caller.

The caller owns all input and output arrays.

## Linking

Implicit linking:
Use Regression.h, RegressionLib.lib,
and RegressionLib.dll.

Define REGRESSION_IMPORTS in the client.

Explicit linking:
Use RegressionLib.dll with
LoadLibrary and GetProcAddress.

Exported functions use C linkage.

## Example

Input:
x = {1, 2, 3, 4, 5}
y = {5, 8, 11, 14, 17}

Expected results:
Slope = 3
Intercept = 2
Prediction for x=6 = 20
R2 = 1
Residuals = {0, 0, 0, 0, 0}

## Compatibility

The supplied binaries are intended
for Windows x64 applications.

API version: 1.0