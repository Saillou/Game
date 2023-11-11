#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera {
    Camera() : projection(glm::mat4()), modelview(glm::mat4()) {  }

    glm::mat4 projection;
    glm::mat4 modelview;
};
