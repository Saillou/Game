#pragma once

#include "../../../Engine/Physx/BaseBody.hpp"

// Public objects
struct BoxBody : public BaseBody {
    // Instance
    BoxBody(const glm::vec3& dimensions, const glm::vec4& color_ = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    virtual ~BoxBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) const override;

    // External data
    glm::vec3 dimensions;

private:
    // Hidden impl details
    void* _impl;
};