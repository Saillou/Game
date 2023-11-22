#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

// -- Scene --
struct IntroScene : public BaseScene {
    IntroScene();

    void draw() override;
    void resize(int width, int height) override;

private:

};
