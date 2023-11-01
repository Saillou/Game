#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "BaseScene.hpp"

struct Window {
    Window(int width, int height, const char* title);
    ~Window();

    bool update();
    void close();

    std::vector<unsigned int> keyPressed();

    // Members
    std::unique_ptr<BaseScene> scene = nullptr;

private:
    GLFWwindow* m_window = nullptr;
};
