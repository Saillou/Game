#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "../../../Engine/Graphic/Base/Light.hpp"
#include "../../../Engine/Graphic/Camera.hpp"
#include "../../../Engine/Graphic/Base/BaseShape.hpp"
#include "../../../Engine/Graphic/Base/Cookable.hpp"

// Objects
struct Box : public Cookable
{
    // Instance
    Box(const glm::vec3& dims);
    virtual ~Box() = default;

    void bind();
    void unbind();

    void draw(const Camera& camera, const glm::vec3& position = {}, const glm::vec3& orientation = {}, const std::vector<std::unique_ptr<Light>>& lights = {});
    void drawBatch(int amount, const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights = {});

    std::shared_ptr<BaseShape> shape();

private:
    // Members
    std::shared_ptr<BaseShape> m_shape;
};