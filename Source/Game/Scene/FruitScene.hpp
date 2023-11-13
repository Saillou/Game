#pragma once

#include <vector>

#include "../../Engine/Graphic/Base/BaseScene.hpp"
#include "Bodies/SphereBody.hpp"
#include "Bodies/FacetteBody.hpp"

struct Fruit : public SphereBody {
    Fruit(float radius_, const glm::vec3& pos_, const glm::vec4& color_);
};

struct Wall : public FacetteBody {
    Wall(const glm::vec3& pos, const glm::vec3& u, const glm::vec3& n, const glm::vec4& color_);
};

// -- Scene --
struct FruitScene : public BaseScene {
    FruitScene();

    void draw() override;
    void resize(int width, int height) override;

    void addWall(std::shared_ptr<Wall> wall);
    void addFruit(std::shared_ptr<Fruit> fruit);

private:
    void _create_shapes();
    void _cook_shapes();
    void _camera_update();

    std::vector<std::shared_ptr<Wall>> m_walls;
    std::vector<std::shared_ptr<Fruit>> m_fruits;
};
