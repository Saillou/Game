#pragma once

#include "../../../Utils/Caster.hpp"
#include "../TextEngine.hpp"
#include "../Camera.hpp"

#include "BaseShape.hpp"

struct BaseScene {
    BaseScene();
    virtual ~BaseScene();

    virtual void draw() = 0;                        // called by an instance of a `Window::update()`
    virtual void resize(int width, int height);     // called by an event `Window::resize()`

protected:
    virtual void _init_gl_config(); // Override this to enable or disable some opengl functionalities. (eg PENCIL_TEST)

    // Members
    Collection m_shapes;
    Camera m_camera = {};

    int m_width  = 0;
    int m_height = 0;
};