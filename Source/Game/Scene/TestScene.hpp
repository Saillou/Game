#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

// -- Scene --
struct TestScene : public BaseScene {
    TestScene();

    void draw() override;
    void resize(int width, int height) override;
};
