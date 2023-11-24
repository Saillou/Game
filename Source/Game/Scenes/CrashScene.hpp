#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

// -- Scene --
struct CrashScene : public BaseScene {
    CrashScene();

    void draw() override;
    void resize(int width, int height) override;

private:

};
