#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"
#include "../../Engine/Graphic/Shaders/ComputeShader.hpp"
#include "../../Engine/Graphic/Utils/StorageBuffer.h"

struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;

private:

};