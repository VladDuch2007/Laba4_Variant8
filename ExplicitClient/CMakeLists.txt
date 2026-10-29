add_executable(ExplicitClient
    main.cpp
)

target_compile_features(ExplicitClient PRIVATE cxx_std_20)

add_custom_command(TARGET ExplicitClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/RegressionSDK/bin/RegressionLib.dll"
    "$<TARGET_FILE_DIR:ExplicitClient>"
)