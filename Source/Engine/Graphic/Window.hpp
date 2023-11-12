#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Base/BaseScene.hpp"

struct Window {
    Window(int width, int height, const char* title);
    ~Window();

    bool update();
    void close();

    // Getters
    int width() const;
    int height() const;
    std::vector<unsigned int> keyPressed();
    std::shared_ptr<BaseScene> scene() const;

    // Setters
    std::shared_ptr<BaseScene> scene(std::shared_ptr<BaseScene> scene);

private:
    void _resize(int width, int height);

    // Members
    GLFWwindow* m_window = nullptr;
    int m_width;
    int m_height;
    std::shared_ptr<BaseScene> m_scene = nullptr;
};
