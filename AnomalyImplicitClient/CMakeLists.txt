
add_executable(AnomalyImplicitClient
    main.cpp
)

target_compile_features(AnomalyImplicitClient PRIVATE
    cxx_std_20
)

target_compile_definitions(AnomalyImplicitClient PRIVATE
    ANOMALY_IMPORTS
)

target_include_directories(AnomalyImplicitClient PRIVATE
    "${CMAKE_SOURCE_DIR}/AnomalySDK/include"
)

target_link_libraries(AnomalyImplicitClient PRIVATE
    "${CMAKE_SOURCE_DIR}/AnomalySDK/lib/AnomalyLib.lib"
)

add_custom_command(TARGET AnomalyImplicitClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/AnomalySDK/bin/AnomalyLib.dll"
    "$<TARGET_FILE_DIR:AnomalyImplicitClient>"
)
