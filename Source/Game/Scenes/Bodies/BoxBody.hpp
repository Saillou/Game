#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "../../../Engine/Graphic/Base/Light.hpp"
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Physx/BaseBody.hpp"

// Public objects
struct BoxBody : public BaseBody {
    // Instance
    BoxBody(const glm::vec3& dimensions, const glm::vec4& color_);
    virtual ~BoxBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) const;

    // External data
    glm::vec3 dimensions;

private:
    // Hidden impl details
    void* _impl;
};