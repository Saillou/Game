#pragma once

#include <glm/glm.hpp>

class BaseBody {
public:
    BaseBody(glm::vec3 position = glm::vec3(0.f), glm::vec3 orientation = glm::vec3(0.f));
    virtual ~BaseBody();

    glm::vec3 position;
    glm::vec3 orientation;
};