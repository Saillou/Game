#pragma once

#include "../../Engine/Graphic/BaseScene.hpp"

struct SimpleScene : public BaseScene {
    SimpleScene() : BaseScene()
    {

    }

    void draw() override {
        glClearColor(0.05f, 0.05f, 0.06f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        TextEngine::Write("Some text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        TextEngine::Write("Yo world!", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
    }
};