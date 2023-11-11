#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"

struct SlimeScene : public BaseScene {
    SlimeScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    void _create_shapes();
    void _cook_shapes();
};