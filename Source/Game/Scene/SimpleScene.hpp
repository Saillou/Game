#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"

struct SimpleScene : public BaseScene {
    SimpleScene();

    void draw() override;

private:
    Shader m_geomShader;
    Shader m_simpleShader;

    Circle m_circle;
    Square m_square;
    Points m_points;
};