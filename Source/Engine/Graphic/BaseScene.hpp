#pragma once

#include "TextEngine.hpp"

struct BaseScene {
    BaseScene();
    virtual ~BaseScene();

    virtual void draw() = 0; // Will be called by an instance of a `Window::update()`

protected:
    virtual void _init_gl_config(); // Override this to enable or disable some opengl functionalities. (eg PENCIL_TEST)
};
