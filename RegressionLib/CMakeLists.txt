add_library(RegressionLib SHARED
    src/Regression.cpp
)

target_compile_definitions(RegressionLib PRIVATE
    REGRESSION_EXPORTS
)

target_include_directories(RegressionLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(RegressionLib PUBLIC cxx_std_20)