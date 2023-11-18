#include "TestCommander.hpp"

#include "../../Engine/Physx/Physx.hpp"
#include "../../Utils/Timer.hpp"

using namespace glm;

// Instance
TestCommander::TestCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<TestScene>(scene))
{    
    // Context 2d
    draw_circle_alive(m_scene, vec2(1.0f, 1.0f), 0.10f,  vec4(0.0f, 0.0f, 1.0f, 1.0f));

    draw_line_dead(m_scene, vec2(-1.0f, 0.0f), vec2(1.0f, 0.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f));
}

// Events
void TestCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    static float theta = 0.0f;

    // React to the emitted keys 
    if (evt.key == Key::Space) {
        
    }

    if (evt.key == Key::ArrowLeft) {
    }

    if (evt.key == Key::ArrowRight) {

    }
}

void TestCommander::_on_mouse_moved(const Event::MouseMoved& evt) {
    std::cout << evt.x << " " << evt.y << std::endl;
}


// -- Drawing helper --
// circles
void TestCommander::draw_circle(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, vec4& color) {
    scene->addCircle(std::make_shared<Circle>(pos, radius, color));
}
void TestCommander::draw_circle_dead(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, vec4& color) {
    Physx::Add(scene->addCircle(std::make_shared<Circle>(pos, radius, color)), Physx::BodyType::Static);
}
void TestCommander::draw_circle_alive(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, vec4& color) {
    Physx::Add(scene->addCircle(std::make_shared<Circle>(pos, radius, color)), Physx::BodyType::Dynamic);
}

// lines
void TestCommander::draw_line(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, vec4& color) {
    scene->addLine(std::make_shared<Line>(pos_start, pos_end, color));
}
void TestCommander::draw_line_dead(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, vec4& color) {
    Physx::Add(scene->addLine(std::make_shared<Line>(pos_start, pos_end, color)), Physx::BodyType::Static);
}
void TestCommander::draw_line_alive(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, vec4& color) {
    Physx::Add(scene->addLine(std::make_shared<Line>(pos_start, pos_end, color)), Physx::BodyType::Dynamic);
}

