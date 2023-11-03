#include "Window.hpp"

#include <vector>
#include <memory>

#include "BaseScene.hpp"

Window::Window(int width, int height, const char* title) : 
    m_width(width), 
    m_height(height)
{
    // Init GLFW
    glfwInit();

    // OpenGL >= 4.0 (for tesselation)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);
    if (!m_window)
        return; // Failure, will close

    // Load gl entry points
    glfwMakeContextCurrent(m_window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Events
    glfwSetWindowUserPointer(m_window, this); // store `this` in m_window's userdata

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* this_window, int new_width, int new_height) {
        ((Window*)(glfwGetWindowUserPointer(this_window)))->_resize(new_width, new_height);
    });
}

Window::~Window() {
    glfwTerminate();
}

// Public
bool Window::update() {
    // To be called in the same thread as the m_window constructor
    glfwMakeContextCurrent(m_window);

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

void Window::close() {
    if (!m_window)
        return;

    glfwSetWindowShouldClose(m_window, true);
}

int Window::width() const {
    return m_width;
}

int Window::height() const {
    return m_height;
}

// Getters
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

// Private
void Window::_resize(int width, int height) {
    glViewport(0, 0, width, height);
    update();
}