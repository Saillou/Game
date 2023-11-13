#pragma once

#include <vector>

#include "../../Engine/Graphic/Base/BaseScene.hpp"
#include "Bodies/SphereBody.hpp"

struct Fruit : public SphereBody {
    Fruit(float radius_, const glm::vec3& pos_, const glm::vec4& color_);
};

// -- Scene --
struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;

    void addFruit(std::shared_ptr<Fruit> fruit);

private:
    void _create_shapes();
    void _cook_shapes();
    void _camera_update();

    std::vector<std::shared_ptr<Fruit>> m_fruits;
};
