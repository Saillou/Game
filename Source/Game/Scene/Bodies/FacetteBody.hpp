#pragma once

#include <array>
#include <glm/glm.hpp>
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Physx/BaseBody.hpp"

// Public objects
struct FacetteBody : public BaseBody {
    typedef std::array<glm::vec3, 4> Quad;

    // Instance
    FacetteBody(const glm::vec3& pos, const glm::vec3& u, const glm::vec3& n, const glm::vec4& color_);
    virtual ~FacetteBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera) const;

    // External data
    glm::vec3 vec_direction;
    glm::vec3 vec_normal;

protected:
    // Internal params
    const float _bouncyness = 1.0f;
    const float _friction   = 1.0f;

    // Internal data
    glm::vec3 _speedPosition;

private:
    // Hidden impl details
    void* _impl;
};