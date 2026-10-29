add_library(AnomalyLib SHARED
    src/Anomaly.cpp
)

target_compile_definitions(AnomalyLib PRIVATE
    ANOMALY_EXPORTS
)

target_include_directories(AnomalyLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(AnomalyLib PUBLIC cxx_std_20)