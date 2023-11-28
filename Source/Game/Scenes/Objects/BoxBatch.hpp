#pragma once

#include "Box.hpp"

// -- Objects --
struct BoxBatch {
    BoxBatch(const glm::vec3& dims, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    void create();
    void draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights);
    void update();

    std::unique_ptr<Box>   object;
    std::vector<glm::mat4> models;
};
