#pragma once

#include <glm/glm.hpp>

#include "../../../Utils/Caster.hpp"
#include "../../../Engine/Graphic/Drawables/BaseShape.hpp"
#include "../../../Engine/Graphic/Shaders/Shader.hpp"
#include "../../../Engine/Graphic/Camera.hpp"

class Fruit : public Object {
    struct _FruitShape : public BaseShape
    {
        _FruitShape(float radius);

        void draw() override;
        void _setAttributes() override;
    };

    Shader m_shader;
    std::shared_ptr<_FruitShape> m_fruit;

public:
    Fruit(float radius);

    void draw(const Camera& camera, const glm::vec3& pos);
};
