#pragma once

#include "../../../Engine/Physx/BaseBody.hpp"

// Public objects
struct SphereBody : public BaseBody {
    SphereBody(float radius_, const glm::vec4& color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    virtual ~SphereBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) const override;

    // External data
    float radius;

private:
    // Hidden impl details
    void* _impl;
};