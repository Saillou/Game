#pragma once

// Include stuff there so it's easier.. to be optimized
#include "TextEngine.hpp"

#include "Shapes/BaseShape.hpp"
#include "Shapes/Rectangle.hpp"

struct BaseScene {
    BaseScene();
    virtual ~BaseScene();

    virtual void draw() = 0;                        // called by an instance of a `Window::update()`
    virtual void resize(int width, int height);     // called by an event `Window::resize()`

protected:
    virtual void _init_gl_config(); // Override this to enable or disable some opengl functionalities. (eg PENCIL_TEST)
};
