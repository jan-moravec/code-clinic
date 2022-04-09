cmake_minimum_required(VERSION 3.0.0)
project(where-am-i VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

# Additional scripts and functions
include(cmake/StandardProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/PreventInSourceBuilds.cmake)
include(cmake/StaticAnalyzers.cmake)

# Enable desired functionality
enable_cppcheck()
enable_clang_tidy()

# Additional libraries
find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

# Executable
add_executable(where-am-i main.cpp)
target_link_libraries(where-am-i PRIVATE fmt::fmt nlohmann_json::nlohmann_json cpr::cpr)
target_compile_features(where-am-i INTERFACE cxx_std_20)

# Warnings as errors
set_project_warnings(where-am-i ON)
