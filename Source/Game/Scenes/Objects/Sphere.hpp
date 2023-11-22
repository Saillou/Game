#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Graphic/Base/Light.hpp"
#include "../../../Engine/Graphic/Base/BaseShape.hpp"
#include "../../../Engine/Graphic/Base/Cookable.hpp"

// Objects
struct Sphere : public Cookable
{
    // Instance
    Sphere(const glm::vec3& center, float radius);
    virtual ~Sphere() = default;

    void draw(const Camera& camera, const glm::vec3& position = {}, const glm::vec3& orientation = {}, const std::vector<std::unique_ptr<Light>>& lights = {});

private:
    void _set_shader_border(UShader&) override;
    void _set_shader_point(UShader&)  override;

    // Members
    std::shared_ptr<BaseShape> m_shape;
};