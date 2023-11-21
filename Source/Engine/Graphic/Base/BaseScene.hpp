#pragma once

#include "../TextEngine.hpp"
#include "../Camera.hpp"

#include "Light.hpp"
#include "Cookable.hpp"
#include "BaseShape.hpp"

// Scene model
struct BaseScene {
    BaseScene();
    virtual ~BaseScene();

    virtual void draw();                            // called by an instance of a `Window::update()`
    virtual void resize(int width, int height);     // called by an event `Window::resize()`

    int width() const;
    int height() const;
    Camera& camera();

protected:
    virtual void _init_gl_config(); // Override this to enable or disable some opengl functionalities. (eg PENCIL_TEST)

    // Members
    CookableCollection m_shapes;
    Camera m_camera = {};
    std::vector<std::unique_ptr<Light>> m_lights;

    int m_width  = 0;
    int m_height = 0;
};