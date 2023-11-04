#pragma once

// Include everything here so it's easier.. may be optimized
#include "TextEngine.hpp"

#include "Shapes/Shape.h"
#include "Shapes/Circle.h"
#include "Shapes/Square.h"
#include "Shapes/Points.h"
#include "Shapes/Quad.h"
#include "Shapes/Icosahedron.h"

struct BaseScene {
    BaseScene();
    virtual ~BaseScene();

    virtual void draw() = 0;                        // called by an instance of a `Window::update()`
    virtual void resize(int width, int height);     // called by an event `Window::resize()`

protected:
    virtual void _init_gl_config(); // Override this to enable or disable some opengl functionalities. (eg PENCIL_TEST)
};
