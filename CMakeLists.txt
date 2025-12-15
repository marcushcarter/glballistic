cmake_minimum_required(VERSION 3.15)
project(glballistic VERSION 0.1 LANGUAGES CXX)

# ========================
# Header-only library
# ========================
add_library(glballistic INTERFACE)

target_include_directories(glballistic INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(glballistic INTERFACE cxx_std_20)

# ========================
# Option to build examples
# ========================
option(BUILD_EXAMPLES "Build example executables" ON)

if(BUILD_EXAMPLES)
    # ------------------------
    # GLAD (manual)
    # ------------------------
    add_library(glad STATIC external/glad/src/glad.c)
    target_include_directories(glad PUBLIC external/glad/include)

    # ------------------------
    # GLFW (submodule)
    # ------------------------
    add_subdirectory(external/glfw)

    # ------------------------
    # Find all example .cpp files recursively
    # ------------------------
    file(GLOB_RECURSE EXAMPLES "examples/**/*.cpp")

    foreach(example_file ${EXAMPLES})
        # Get folder name containing main.cpp
        get_filename_component(example_path ${example_file} PATH)
        get_filename_component(folder_name ${example_path} NAME)

        # Get filename without extension
        get_filename_component(example_name ${example_file} NAME_WE)

        # Combine folder + file for unique executable name
        set(exec_name "${folder_name}_${example_name}")

        # Create executable
        add_executable(${exec_name} ${example_file})

        # Link against header-only library + GLAD + GLFW
        target_link_libraries(${exec_name} PRIVATE glballistic glad glfw)

        # Ensure C++20
        target_compile_features(${exec_name} PRIVATE cxx_std_20)
    endforeach()
endif()
