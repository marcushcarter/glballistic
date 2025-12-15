# GLBallistic

GLBallistic is a header-only C++ OpenGL utility library for high-performance graphics applications and game engines. It provides modern, clean abstractions for OpenGL objects and state management, optimized for efficiency and ease of use.

## Features

- **Header-only C++20 library** – integrate by simply including headers.
- **State caching** – minimizes redundant OpenGL calls for textures, buffers, shaders, and vertex arrays.
- **Direct State Access (DSA) support** – uses modern OpenGL functions when available (4.5+).
- **Compute shader ready** – easily bind textures and buffers for GPU compute workloads.
- **Flexible texture system** – 2D textures with plans for 1D, 3D, cube maps, and array textures.
- **Cross-platform examples** – includes GLFW + GLAD examples demonstrating core features.

## Installation

1. Clone the repository:

```bash
git clone https://github.com/marcushcarter/glballistic.git
cd glballistic
```

2. Add GLBallistic as a header-only library in your CMake project:

```bash
add_subdirectory(path/to/glballistic)
target_link_libraries(your_project PRIVATE glballistic)
```

3. Ensure your project uses C++20:

```bash
target_compile_features(your_project PRIVATE cxx_std_20)
```

## Examples

The repository includes example programs demonstrating:

- Basic rendering setup with OpenGL
- Texture creation and binding
- Buffer and vertex array management
- Compute shader texture usage

To build examples, configure CMake with `BUILD_EXAMPLES` enabled (default ON for top-level builds). GLFW and GLAD are included as part of the examples build.

## Contributing

Contributions are welcome. Please fork the repository and submit pull requests. Ensure that new functionality remains header-only and respects the library’s performance-oriented design.

## License

This project is released under the MIT License.
