#pragma once

#include <array>
#include <glm/glm.hpp>
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Physx/BaseBody.hpp"

// Public objects
struct FacetteBody : public BaseBody {
    // Instance
    FacetteBody(const glm::vec3& pos, const glm::vec3& u, const glm::vec3& n, const glm::vec4& color_);
    virtual ~FacetteBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera) const;

    // External data
    glm::vec3 vec_direction;
    glm::vec3 vec_normal;

private:
    // Hidden impl details
    void* _impl;
};