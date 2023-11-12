#pragma once

// Include stuff there so it's easier.. to be optimized
#include "TextEngine.hpp"
#include "BaseShape.hpp"
#include "Camera.hpp"

#include "../Events/Events.hpp"
#include "../../Utils/Caster.hpp"

struct BaseScene : public Event::Subscriber {
    BaseScene();
    virtual ~BaseScene();

    virtual void draw() = 0;                        // called by an instance of a `Window::update()`
    virtual void resize(int width, int height);     // called by an event `Window::resize()`

protected:
    virtual void _init_gl_config(); // Override this to enable or disable some opengl functionalities. (eg PENCIL_TEST)

    virtual void _on_key_pressed(const Event::KeyPressed&);

    // Members
    Collection m_shapes;
    Camera m_camera = {};

    int m_width  = 0;
    int m_height = 0;
};