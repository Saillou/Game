#pragma once

#include <array>
#include <glm/glm.hpp>

#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Graphic/Base/BaseShape.hpp"
#include "../../../Engine/Graphic/Base/Cookable.hpp"

// Objects
struct Sphere : public Cookable
{
    // Instance
    Sphere(const glm::vec3& center, float radius);
    virtual ~Sphere() = default;

    void draw(const Camera& camera, const glm::vec3& position = glm::vec3(), const glm::vec3& orientation = glm::vec3());

private:
    void _set_shader_border(UShader&) override;
    void _set_shader_point(UShader&)  override;

    // Members
    std::shared_ptr<BaseShape> m_shape;
};