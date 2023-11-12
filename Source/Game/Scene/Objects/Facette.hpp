#pragma once

#include <array>
#include <glm/glm.hpp>

#include "../../../Utils/Caster.hpp"
#include "../../../Engine/Graphic/Shaders/Shader.hpp"
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Graphic/Base/BaseShape.hpp"

// Objects
struct Facette : public Object {
    // Enums and type
    typedef std::array<glm::vec3, 4> Quad;

    enum class CookType {
        Solid, Border, Point
    };

    // Instance
    Facette(const Quad& points);
    Facette(const glm::vec3& center, const glm::vec3& u, const glm::vec3& n);

    virtual ~Facette() = default;

    Facette* addRecipe(const CookType& type, const glm::vec4& color);
    void draw(const Camera& camera, const glm::vec3& position = glm::vec3());

private:
    // Members
    std::shared_ptr<BaseShape> m_shape;
    std::vector<UShader> m_shaders;
};