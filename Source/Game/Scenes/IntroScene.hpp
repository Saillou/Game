#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include <vector>
#include <memory>
#include "Objects/Sphere.hpp"

// -- Objects --
struct SphereBatch {
    SphereBatch(float radius);

    void create();
    void draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights);

    std::unique_ptr<Sphere> object;
    std::vector<glm::mat4>  models;
};

// -- Scene --
struct IntroScene : public BaseScene {
    IntroScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    void _update_camera();
    const std::vector<glm::vec2> _get_title_pos() const;

    SphereBatch m_decors;
    SphereBatch m_title;
};
