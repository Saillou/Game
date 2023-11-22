#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "../../../Engine/Graphic/Base/Light.hpp"
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Physx/BaseBody.hpp"

// Public objects
struct SphereBody : public BaseBody {
    SphereBody(float radius_, const glm::vec4& color_);
    virtual ~SphereBody();

    // Method
    virtual int id() const;
    virtual void draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) const;

    // External data
    float radius;

private:
    // Hidden impl details
    void* _impl;
};