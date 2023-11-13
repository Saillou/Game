#pragma once

#include <glm/glm.hpp>
#include "../../../Engine/Graphic/Camera.hpp"

// Public objects
struct SphereBody {
    SphereBody(float radius_, const glm::vec3& position_, const glm::vec4& color_);
    virtual ~SphereBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera) const;

    // External data
    float radius;
    glm::vec3 position;
    glm::vec3 orientation;

protected:
    // Internal params
    const float _bouncyness = 1.0f;
    const float _friction   = 1.0f;

    // Internal data
    glm::vec3 _speedPosition;
    glm::vec3 _speedOrientation;

private:
    // Hidden impl details
    void* _impl;
};