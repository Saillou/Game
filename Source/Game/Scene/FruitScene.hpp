#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"


// -- Scene --
struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;
};
