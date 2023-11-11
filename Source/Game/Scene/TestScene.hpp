#pragma once

#include "../../Utils/Caster.hpp"
#include "../../Engine/Graphic/Camera.hpp"
#include "../../Engine/Graphic/BaseScene.hpp"


// -- Scene --
struct TestScene : public BaseScene {
    TestScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    Collection m_shapes;
    Camera m_camera;
};
