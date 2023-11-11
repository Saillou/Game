#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"

struct CrashScene : public BaseScene {
    CrashScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    void _create_shapes();
    void _cook_shapes();
};