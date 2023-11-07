#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"
#include "../../Engine/Graphic/Shaders/ComputeShader.hpp"
#include "../../Engine/Graphic/Utils/StorageBuffer.h"

struct TesselScene : public BaseScene {
    TesselScene();

    void draw() override;
    void resize(int width, int height) override;

private:
    ComputeShader m_physx;
    StorageBuffer<float> m_input;
    StorageBuffer<float> m_output;

    std::unordered_map<std::string, Shader> m_shaders;
    glm::mat4 m_projection;
    glm::mat4 m_modelview;
    Quad m_shapeGround;
};