#pragma once

#include <vector>
#include <memory>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "BaseScene.hpp"

struct Window {
    Window(int width, int height, const char* title) {
        // Init GLFW
        glfwInit();

        // OpenGL >= 4.0 (for tesselation)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

    ~Window() {
        glfwTerminate();
    }

    bool update() {
        if (!m_window)
            return false;

        if (scene)
            scene->draw();

        glfwSwapBuffers(m_window);
        glfwPollEvents();

        return !glfwWindowShouldClose(m_window);
    }

    std::vector<unsigned int> keyPressed() {
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

    void close() {
        if (!m_window)
            return;

        glfwSetWindowShouldClose(m_window, true);
    }

    // Members
    std::unique_ptr<BaseScene> scene = nullptr;

private:
    GLFWwindow* m_window = nullptr;
};
