add_executable(AnomalyTest
    main.cpp
)

target_link_libraries(AnomalyTest PRIVATE
    AnomalyLib
)

target_compile_definitions(AnomalyTest PRIVATE
    ANOMALY_IMPORTS
)

target_compile_features(AnomalyTest PRIVATE cxx_std_20)

add_custom_command(TARGET AnomalyTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:AnomalyLib>"
    "$<TARGET_FILE_DIR:AnomalyTest>"
)