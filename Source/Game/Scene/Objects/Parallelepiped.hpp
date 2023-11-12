#pragma once

#include <array>
#include <glm/glm.hpp>

#include "../../../Utils/Caster.hpp"
#include "../../../Engine/Graphic/Base/BaseShape.hpp"
#include "../../../Engine/Graphic/Shaders/Shader.hpp"
#include "../../../Engine/Graphic/Camera.hpp"

// Objects
struct Parallelepiped : public Object {
    // Enums and type
    typedef std::array<glm::vec3, 4> Quad;

    enum class CookType {
        Solid, Border, Point
    };

    // Instance
    Parallelepiped(const glm::vec3& center, const glm::vec3& u, const glm::vec3& n, const glm::vec3& w);

    virtual ~Parallelepiped() = default;

    Parallelepiped* addRecipe(const CookType& type, const glm::vec4& color);
    void draw(const Camera& camera, const glm::vec3& position = glm::vec3());

private:
    // Members
    std::shared_ptr<BaseShape> m_shape;
    std::vector<UShader> m_shaders;
};