# Build entire gtest project
# All source files from src folder should be compiled

# Minimum cmake version required is 3.10
cmake_minimum_required(VERSION 3.10)

# Project name: networktester
project(networktester)

# Add source files (All files in src folder)
file(GLOB sourcefiles "src/*.cpp")
add_executable(networktester ${sourcefiles})

# Use C++17 standard
set_target_properties(networktester PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED True)

# Add libraries
target_link_libraries(networktester
    -pthread
    -lgtest)
