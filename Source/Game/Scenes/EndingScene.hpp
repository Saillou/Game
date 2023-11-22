#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

// -- Scene --
struct EndingScene : public BaseScene {
    EndingScene();

    void draw() override;
    void resize(int width, int height) override;

private:

};
