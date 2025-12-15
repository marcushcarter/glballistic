cmake_minimum_required(VERSION 3.15)
project(glballistic VERSION 0.1 LANGUAGES CXX)

# Header-only library
add_library(glballistic INTERFACE)
target_include_directories(glballistic INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(glballistic INTERFACE cxx_std_20)

# Only build examples if this is the top-level project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(BUILD_EXAMPLES "Build example executables" ON)
else()
    set(BUILD_EXAMPLES OFF)
endif()

if(BUILD_EXAMPLES)
    # Build GLAD for examples only
    add_library(glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c")
    target_include_directories(glad PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include")

    # Build GLFW for examples only if available
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
        add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/glfw")
    else()
        message(WARNING "GLFW not found, examples may not build")
    endif()

    # Find example source files recursively
    file(GLOB_RECURSE EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
    foreach(example_file ${EXAMPLES})
        get_filename_component(example_path ${example_file} PATH)
        get_filename_component(folder_name ${example_path} NAME)
        get_filename_component(example_name ${example_file} NAME_WE)
        set(exec_name "${folder_name}_${example_name}")

        add_executable(${exec_name} ${example_file})
        target_link_libraries(${exec_name} PRIVATE glballistic glad glfw)
        target_compile_features(${exec_name} PRIVATE cxx_std_20)
    endforeach()
endif()
