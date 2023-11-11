#pragma once

#include <array>
#include <glm/glm.hpp>

#include "../../../Utils/Caster.hpp"
#include "../../../Engine/Graphic/Drawables/BaseShape.hpp"
#include "../../../Engine/Graphic/Shaders/Shader.hpp"
#include "../../../Engine/Graphic/Camera.hpp"

// Objects
struct Sphere : public Object {
    // Enums and type
    typedef std::array<glm::vec3, 4> Quad;

    enum class CookType {
        Solid, Border, Point
    };

    // Instance
    Sphere(const glm::vec3& center, float radius);
    virtual ~Sphere() = default;

    Sphere* addRecipe(const CookType& type, const glm::vec4& color);
    void draw(const Camera& camera, const glm::vec3& position = glm::vec3());

private:
    // Members
    std::shared_ptr<BaseShape> m_shape;
    std::vector<UShader> m_shaders;
};