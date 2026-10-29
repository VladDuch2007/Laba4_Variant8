add_executable(ImplicitClient
    main.cpp
)

target_compile_features(ImplicitClient PRIVATE cxx_std_20)

target_compile_definitions(ImplicitClient PRIVATE
    REGRESSION_IMPORTS
)

target_include_directories(ImplicitClient PRIVATE
    "${CMAKE_SOURCE_DIR}/RegressionSDK/include"
)

target_link_libraries(ImplicitClient PRIVATE
    "${CMAKE_SOURCE_DIR}/RegressionSDK/lib/RegressionLib.lib"
)

add_custom_command(TARGET ImplicitClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/RegressionSDK/bin/RegressionLib.dll"
    "$<TARGET_FILE_DIR:ImplicitClient>"
)