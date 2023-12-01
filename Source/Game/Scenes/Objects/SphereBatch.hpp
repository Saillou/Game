#pragma once

#include "Sphere.hpp"

// -- Objects --
struct SphereBatch {
    SphereBatch(float radius, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    void create();
    void draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights);
    void update();

    std::unique_ptr<Sphere> object;
    std::vector<glm::mat4>  models;
};
