#include <glballistic/all.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSrc = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0); // orange
}
)";

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    float vertices[] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    gl::VertexArray vao;
    vao.create();

    gl::Buffer vbo;
    vbo.create(GL_ARRAY_BUFFER);
    vbo.data(sizeof(vertices), vertices, GL_STATIC_DRAW);

    vao.vertexBuffer(0, vbo, 0, 3 * sizeof(float));
    vao.vertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    vao.enableAttrib(0);

    gl::Shader shader;
    shader.create();
    shader.attachShader(GL_VERTEX_SHADER, vertexShaderSrc);
    shader.attachShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    shader.link();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        vao.drawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();
    shader.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
