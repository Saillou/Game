#pragma once

#include "../../Engine/Graphic/Base/BaseScene.hpp"

#include "Bodies/SphereBody.hpp"
#include "Bodies/BoxBody.hpp"

struct Circle : public SphereBody {
    Circle(const glm::vec2& pos_, float radius_, const glm::vec4& color_);
};

struct Line : public BoxBody {
    Line(const glm::vec2& pt_a, const glm::vec2& pt_b, const glm::vec4& color_);
};

// -- Scene --
struct TestScene : public BaseScene {
    TestScene();

    std::shared_ptr<Line>  addLine(std::shared_ptr<Line> line);
    std::shared_ptr<Circle> addCircle(std::shared_ptr<Circle> circle);

    void draw() override;
    void resize(int width, int height) override;

private:
    void _camera_update();

    std::vector<std::shared_ptr<SphereBody>> m_spheres;
    std::vector<std::shared_ptr<BoxBody>> m_boxes;
};
