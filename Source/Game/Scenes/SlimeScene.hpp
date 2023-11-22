#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

// -- Scene --
struct SlimeScene : public BaseScene {
    SlimeScene();

    void draw() override;
    void resize(int width, int height) override;

private:

};
