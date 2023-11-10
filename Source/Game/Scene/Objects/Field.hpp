#pragma once

#include <array>
#include <glm/glm.hpp>

#include "../../../Utils/Caster.hpp"
#include "../../../Engine/Graphic/Drawables/BaseShape.hpp"
#include "../../../Engine/Graphic/Shaders/Shader.hpp"
#include "../../../Engine/Graphic/Camera.hpp"

// Objects
class Field : public Object {
    struct _FaceShape : public BaseShape {
        _FaceShape(const std::array<glm::vec3, 4>& quad);

        void draw() override;
        void _setAttributes() override;
    };

    struct _FieldShape : public BaseShape {
        _FieldShape(float width, float depth, float height);

        void draw() override;
        void _setAttributes() override;
    };

    Shader m_shaderGeom;
    Shader m_shaderSolid;
    std::shared_ptr<_FieldShape> m_borderBack;
    std::vector<std::shared_ptr<_FaceShape>> m_surfaceBack;

public:
    Field(float width, float depth, float height);
    void draw(const Camera& camera, const glm::vec3& pos);
};