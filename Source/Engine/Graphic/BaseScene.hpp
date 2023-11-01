#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Engine/Graphic/TextEngine.hpp"

struct BaseScene {
    BaseScene() {
        _init_gl_config();
    }

    virtual ~BaseScene() {  }

    virtual void draw() = 0;

protected:
    virtual void _init_gl_config() {
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_PROGRAM_POINT_SIZE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
};
