add_executable(RegressionTest
    main.cpp
)

target_link_libraries(RegressionTest PRIVATE
    RegressionLib
)

target_compile_definitions(RegressionTest PRIVATE
    REGRESSION_IMPORTS
)

target_compile_features(RegressionTest PRIVATE cxx_std_20)

add_custom_command(TARGET RegressionTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:RegressionLib>"
        "$<TARGET_FILE_DIR:RegressionTest>"
)