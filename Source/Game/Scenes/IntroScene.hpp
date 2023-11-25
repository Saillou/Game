#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include <vector>
#include <memory>
#include "Objects/Sphere.hpp"

// -- Scene --
struct IntroScene : public BaseScene {
    IntroScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    void _update_camera();

    std::unique_ptr<Sphere> m_planet;
    std::vector<glm::mat4> m_planets_pose;
};
