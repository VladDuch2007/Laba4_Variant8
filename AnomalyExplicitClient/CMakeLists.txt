
add_executable(AnomalyExplicitClient
    main.cpp
)

target_compile_features(AnomalyExplicitClient PRIVATE
    cxx_std_20
)

add_custom_command(TARGET AnomalyExplicitClient POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/AnomalySDK/bin/AnomalyLib.dll"
    "$<TARGET_FILE_DIR:AnomalyExplicitClient>"
)
