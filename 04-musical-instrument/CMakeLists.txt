cmake_minimum_required(VERSION 3.0.0)
project(musical-instrument VERSION 0.1.0)

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
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Executable
add_executable(${CMAKE_PROJECT_NAME} main.cpp window.cpp sound.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE fmt::fmt SDL2::SDL2 SDL2::SDL2main ${OPENGL_LIBRARIES} imgui::imgui)
target_compile_features(${CMAKE_PROJECT_NAME} INTERFACE cxx_std_20)

# Warnings as errors
set_project_warnings(${CMAKE_PROJECT_NAME} ON)
