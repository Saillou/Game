#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera {
    Camera() : projection(glm::mat4()), modelview(glm::mat4()) {  }

    // Members
    glm::mat4 projection = {};
    glm::mat4 modelview  = {};

    // TODO: 
    // refacto this part to only expose what's necessary (create helpers if needed)
    glm::mat4 lookAt(const glm::vec3& up) {
        return glm::lookAt(position, direction, up);
    }

    glm::mat4 perspective(float aspect) {
        return glm::perspective(glm::radians<float>(30.0f), aspect, 0.1f, 100.0f);
    }

    glm::mat4 ortho(float aspect) {
        return glm::ortho(-aspect, +aspect, -1.0f, 1.0f, 0.1f, 100.0f);
    }

    glm::vec3 position  = {};
    glm::vec3 direction = {};
    float fieldOfView   = 0.0f;
};
