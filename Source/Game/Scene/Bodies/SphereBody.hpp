#pragma once

#include <glm/glm.hpp>
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Physx/BaseBody.hpp"

// Public objects
struct SphereBody : public BaseBody {
    SphereBody(float radius_, const glm::vec3& position_, const glm::vec4& color_);
    virtual ~SphereBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera) const;

    // External data
    float radius;

private:
    // Hidden impl details
    void* _impl;
};