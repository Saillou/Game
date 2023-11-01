#include <iostream>
#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    // Init GLFW
    glfwInit();

    // OpenGL >= 4.0 (for tesselation)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    auto window = glfwCreateWindow(800, 600, "Game", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout << "Success" << std::endl;
    else
        std::cout << "Failure" << std::endl;

    return 0;
}