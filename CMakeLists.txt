cmake_minimum_required(VERSION 3.15)
project(glballistic VERSION 0.1 LANGUAGES CXX)

# Header-only library
add_library(glballistic INTERFACE)

# Include directories
target_include_directories(glballistic INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Enforce C++20 for consumers
target_compile_features(glballistic INTERFACE cxx_std_20)
