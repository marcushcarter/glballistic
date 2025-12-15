#include <glballistic/all.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

const char* computeShaderSrc = R"(
#version 430 core
layout (local_size_x = 16, local_size_y = 16) in;

layout (rgba32f, binding = 0) uniform image2D imgOutput;

void main() {
    ivec2 pixel = ivec2(gl_GlobalInvocationID.xy);
    vec2 uv = vec2(pixel) / vec2(imageSize(imgOutput));
    
    // simple gradient raytracer
    vec3 color = vec3(uv, 0.5);
    imageStore(imgOutput, pixel, vec4(color, 1.0));
}
)";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Compute Raytracer", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    gl::Texture2D renderTex;
    renderTex.create(800, 600, GL_RGBA32F, GL_RGBA, GL_FLOAT);
    renderTex.setParameters(GL_NEAREST, GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

    gl::Shader computeShader;
    computeShader.create();
    computeShader.attachShader(GL_COMPUTE_SHADER, computeShaderSrc);
    computeShader.link();

    float quadVerts[] = {
        -1.f, -1.f,
         1.f, -1.f,
        -1.f,  1.f,
         1.f,  1.f
    };
    gl::VertexArray quadVAO;
    quadVAO.create();
    gl::Buffer quadVBO;
    quadVBO.create(GL_ARRAY_BUFFER);
    quadVBO.data(sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
    quadVAO.vertexBuffer(0, quadVBO.get(), 0, 2 * sizeof(float));
    quadVAO.vertexAttrib(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    quadVAO.enableAttrib(0);

    const char* vs = R"(
    #version 330 core
    layout(location=0) in vec2 aPos;
    out vec2 uv;
    void main() {
        uv = aPos * 0.5 + 0.5;
        gl_Position = vec4(aPos, 0.0, 1.0);
    })";
    const char* fs = R"(
    #version 330 core
    out vec4 FragColor;
    in vec2 uv;
    uniform sampler2D screenTex;
    void main() {
        FragColor = texture(screenTex, uv);
    })";

    gl::Shader screenShader;
    screenShader.create();
    screenShader.attachShader(GL_VERTEX_SHADER, vs);
    screenShader.attachShader(GL_FRAGMENT_SHADER, fs);
    screenShader.link();

    while (!glfwWindowShouldClose(window)) {
        gl::Clear();

        computeShader.use();
        renderTex.bindImage(0, GL_WRITE_ONLY);
        computeShader.dispatchCompute((800 + 15)/16, (600 + 15)/16, 1, GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

        screenShader.use();
        renderTex.bind(0);
        quadVAO.drawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    renderTex.destroy();
    quadVBO.destroy();
    quadVAO.destroy();
    computeShader.destroy();
    screenShader.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
