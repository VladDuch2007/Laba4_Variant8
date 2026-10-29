cmake_minimum_required(VERSION 3.20)

project(Lab_4_Vladyslav LANGUAGES CXX)

add_subdirectory(RegressionLib)

add_subdirectory(App)

add_subdirectory(ImplicitClient)
add_subdirectory(ExplicitClient)

add_subdirectory(AnomalyLib)
add_subdirectory(AnomalyApp)

add_subdirectory(AnomalyImplicitClient)
add_subdirectory(AnomalyExplicitClient)