#include "Camera.hpp"

Camera::Camera() : 
    projection(glm::mat4()), 
    modelview(glm::mat4())
{
    // ..
}

// Helpers
void Camera::lookAt(const glm::vec3& up) {
    modelview = glm::lookAt(position, direction, up);
}

void Camera::usePerspective(float aspect) {
    projection = glm::perspective(glm::radians<float>(30.0f), aspect, 0.1f, 100.0f);
}

void Camera::useOrtho(float aspect) {
    projection = glm::ortho(-aspect, +aspect, -1.0f, 1.0f, 0.1f, 100.0f);
}

