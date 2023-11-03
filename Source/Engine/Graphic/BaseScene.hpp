#pragma once

// Include everything here so it's easier.. may be optimized
#include "TextEngine.hpp"

#include "Shape.h"
#include "Circle.h"
#include "Square.h"
#include "Points.h"
#include "Quad.h"
#include "Icosahedron.h"

struct BaseScene {
    BaseScene();
    virtual ~BaseScene();

    virtual void draw() = 0;                        // called by an instance of a `Window::update()`
    virtual void resize(int width, int height) = 0; // called by an event `Window::resize()`

protected:
    virtual void _init_gl_config(); // Override this to enable or disable some opengl functionalities. (eg PENCIL_TEST)
};
