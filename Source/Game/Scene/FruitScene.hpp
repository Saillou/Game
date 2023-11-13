#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

// -- Scene --
struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    void _create_shapes();
    void _cook_shapes();
    void _camera_update();
};
