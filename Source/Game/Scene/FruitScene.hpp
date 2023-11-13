#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

// -- Scene --
struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;

    void moveCameraPosition(float dx, float dy, float dz);
    void moveCameraDirection(float dx, float dy, float dz);
    void changeCameraPerspective(float dfov);

private:
    void _create_shapes();
    void _cook_shapes();
    void _camera_update();

    glm::vec3 _camPos;
    glm::vec3 _camDir;
    glm::float32 _angle;
};
