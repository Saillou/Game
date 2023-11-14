#pragma once

#include <array>
#include <glm/glm.hpp>

#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Graphic/Base/BaseShape.hpp"
#include "../../../Engine/Graphic/Base/Cookable.hpp"

// Objects
struct Facette : public Cookable
{
    // Enums and type
    typedef std::array<glm::vec3, 4> Quad;

    // Instance
    Facette(const Quad& points);
    Facette(const glm::vec3& center, const glm::vec3& u, const glm::vec3& n);

    virtual ~Facette() = default;

    void draw(const Camera& camera, const glm::vec3& position = glm::vec3());

private:
    void _set_shader_common(UShader&);
    void _set_shader_solid(UShader&)  override;
    void _set_shader_border(UShader&) override;
    void _set_shader_point(UShader&)  override;

    // Members
    std::shared_ptr<BaseShape> m_shape;
};