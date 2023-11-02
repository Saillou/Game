#include "Window.hpp"

#include <vector>
#include <memory>

#include "BaseScene.hpp"

Window::Window(int width, int height, const char* title) {
    // Init GLFW
    glfwInit();

    // OpenGL >= 4.0 (for tesselation)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_window)
        return; // Failure, will close

    glfwMakeContextCurrent(m_window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

Window::~Window() {
    glfwTerminate();
}

bool Window::update() {
    // Can't continue states
    if (!m_window)
        return false;

    if (glfwWindowShouldClose(m_window))
        return false;

    // Ok
    if (scene)
        scene->draw();

    glfwSwapBuffers(m_window);
    glfwPollEvents();

    return true;
}

std::vector<unsigned int> Window::keyPressed() {
    if (!m_window)
        return {};

    std::vector<unsigned int> keys;
    keys.reserve(GLFW_KEY_LAST + 1);

    for (unsigned int key = 0; key <= GLFW_KEY_LAST; key++) {
        if (glfwGetKey(m_window, key) == GLFW_PRESS) {
            keys.push_back(key);
        }
    }

    return keys;
}

void Window::close() {
    if (!m_window)
        return;

    glfwSetWindowShouldClose(m_window, true);
}
