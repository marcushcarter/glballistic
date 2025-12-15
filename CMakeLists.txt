add_library(glballistic INTERFACE)
target_include_directories(glballistic INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(glballistic INTERFACE cxx_std_20)