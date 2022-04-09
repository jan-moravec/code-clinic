cmake_minimum_required(VERSION 3.0.0)
project(weather-statistics VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

# Additional scripts and functions
include(cmake/StandardProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/PreventInSourceBuilds.cmake)
include(cmake/StaticAnalyzers.cmake)

# Enable desired functionality
enable_cppcheck()
enable_clang_tidy()

add_executable(weather-statistics main.cpp WeatherStatistics.cpp)
target_compile_features(weather-statistics INTERFACE cxx_std_20)
set_project_warnings(weather-statistics ON)
