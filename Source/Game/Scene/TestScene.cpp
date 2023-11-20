#include "TestScene.hpp"

#include "Objects/Box.hpp"
#include "Objects/Sphere.hpp"

#include <glm/gtx/string_cast.hpp>

// Objects
Circle::Circle(const glm::vec2& pos_, float radius_, const glm::vec4& color_):
    SphereBody(radius_, color_)
{
    position    = glm::vec3(-pos_.x, 0.0f, pos_.y);
    orientation = glm::vec3(0.0f);
}

Line::Line(const glm::vec2& pt_a, const glm::vec2& pt_b, const glm::vec4& color_):
    BoxBody(glm::vec3(glm::distance(pt_a, pt_b)*0.5f, 0.005f, 0.005f), color_)
{
    position = glm::vec3(-(pt_a.x+pt_b.x)*0.5f, 0.0f, (pt_a.y+pt_b.y)*0.5f);
    orientation.y = glm::acos(glm::clamp(glm::dot(glm::normalize(pt_b - pt_a), glm::normalize(glm::vec2(-1.0f, 0.0f))), -1.0f, +1.0f));
}

// Scene instance
TestScene::TestScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 3.8f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camera.fieldOfView = 45.0f;
}

void TestScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _camera_update();
}

std::shared_ptr<Line>  TestScene::addLine(std::shared_ptr<Line> line) {
    m_boxes.push_back(line);
    return line;
}

std::shared_ptr<Circle> TestScene::addCircle(std::shared_ptr<Circle> circle) {
    m_spheres.push_back(circle);
    return circle;
}

void TestScene::draw() {
    // Get camera
    _camera_update();

    for (auto& shape : m_boxes) {
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

    // Example: mouvement 2D
    m_camera.projection = m_camera.ortho(aspect);

    // Example: mouvement 3D
    //static float theta = 0.0f;
    //theta += 0.02f;
    //m_camera.position = glm::vec3(3.8f*sin(theta), 3.8f*cos(theta), 0.0f);
    //m_camera.projection = m_camera.perspective(aspect);
}