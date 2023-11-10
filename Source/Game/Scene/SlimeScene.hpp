#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"

struct SlimeScene : public BaseScene {
    SlimeScene();

    void draw() override;
    void resize(int width, int height) override;
};