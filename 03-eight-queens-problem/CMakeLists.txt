cmake_minimum_required(VERSION 3.0.0)
project(eight-queens-problem VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

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
find_package(ftxui CONFIG REQUIRED)

# Executable
add_executable(${CMAKE_PROJECT_NAME} main.cpp Board.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE fmt::fmt ftxui::dom ftxui::screen ftxui::component)
target_compile_features(${CMAKE_PROJECT_NAME} INTERFACE cxx_std_20)

# Warnings as errors
set_project_warnings(${CMAKE_PROJECT_NAME} ON)
