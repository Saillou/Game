#include "TestScene.hpp"

#include "Objects/Parallelepiped.hpp"
#include "Objects/Sphere.hpp"

#include <glm/gtx/string_cast.hpp>

Circle::Circle(const glm::vec2& pos_, float radius_, const glm::vec4& color_):
    SphereBody(radius_, glm::vec3(-pos_.x, 0.0f, pos_.y), color_)
{
}

Line::Line(const glm::vec2& pt_a, const glm::vec2& pt_b, const glm::vec4& color_):
    ParallelipipedBody(
        0.5f * glm::vec3(-pt_a.x - pt_b.x, 0.0f, pt_a.y + pt_b.y),
        1.0f * glm::vec3(-pt_b.x + pt_a.x, 0.0f, pt_b.y - pt_a.y),
        0.005f * glm::normalize(glm::vec3(-pt_b.y + pt_a.y, 0.0f, -pt_b.x + pt_a.x)),
        0.005f * glm::normalize(glm::cross(glm::vec3(-pt_b.x + pt_a.x, 0.0f, pt_b.y - pt_a.y), glm::vec3(-pt_b.y + pt_a.y, 0.0f, -pt_b.x + pt_a.x))),
        color_)
{

}


// Scene instance
TestScene::TestScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 10.0f, 0.5f);
    m_camera.direction   = glm::vec3(0.0f, 0.0f, 0.5f);
    m_camera.fieldOfView = 10.0f;
}

void TestScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _camera_update();
}

std::shared_ptr<Line>  TestScene::addLine(std::shared_ptr<Line> line) {
    m_facettes.push_back(line);
    return line;
}

std::shared_ptr<Circle> TestScene::addCircle(std::shared_ptr<Circle> circle) {
    m_spheres.push_back(circle);
    return circle;
}

void TestScene::draw() {
    // Get camera
    _camera_update();

    for (auto& shape : m_facettes) {
        shape->draw(m_camera);
    }

    for (auto& shape : m_spheres) {
        shape->draw(m_camera);
    }

    // Draw texts
    TextEngine::Write("Test Scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void TestScene::_camera_update() {
    float aspect = (float)m_width / m_height;

    m_camera.modelview = m_camera.lookAt(glm::vec3(0, 0, 1));
    m_camera.projection = m_camera.ortho(aspect);
}