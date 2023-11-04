#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"

struct ExperimentalScene : public BaseScene {
    ExperimentalScene();

    void draw() override;
    void resize(int width, int height) override;
};