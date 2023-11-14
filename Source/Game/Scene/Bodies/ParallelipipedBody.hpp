#pragma once

#include <array>
#include <glm/glm.hpp>
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Physx/BaseBody.hpp"

// Public objects
struct ParallelipipedBody : public BaseBody {
    // Instance
    ParallelipipedBody(const glm::vec3& pos, const glm::vec3& u, const glm::vec3& n, const glm::vec3& w, const glm::vec4& color_);
    virtual ~ParallelipipedBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera) const;

    // External data
    glm::vec3 vec_direction;
    glm::vec3 vec_normal;
    glm::vec3 vec_height;

private:
    // Hidden impl details
    void* _impl;
};