#include "TestCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"
#include "../../Utils/Timer.hpp"

using namespace glm;

// Instance
TestCommander::TestCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<TestScene>(scene))
{    
    // Context 2d
    m_sphere_preview = draw_circle(m_scene, vec2(1.0f, 1.0f), 0.10f,  vec4(0.0f, 0.0f, 1.0f, 1.0f));
    
    float size = 1.0f;
    const vec2 A(-size, -size);
    const vec2 B(-size, +size);
    const vec2 C(+size, +size);
    const vec2 D(+size, -size);

    draw_line(m_scene, A, B, vec4(1.0f, 1.0f, 0.0f, 1.0f));
    draw_line(m_scene, B, C, vec4(1.0f, 1.0f, 0.0f, 1.0f));
    draw_line(m_scene, C, D, vec4(1.0f, 1.0f, 0.0f, 1.0f));
    draw_line_dead(m_scene, D, A, vec4(1.0f, 1.0f, 0.0f, 1.0f));
}

// Events
void TestCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    static float theta = 0.0f;

    // React to the emitted keys 
    if (evt.key == Key::Space) {
        if (!m_launched) {
            m_launched = true;

            Physx::Add(m_sphere_preview, Physx::BodyType::Dynamic);
        }
    }

    if (evt.key == Key::ArrowLeft) {

    }

    if (evt.key == Key::ArrowRight) {

    }
}

void TestCommander::_on_mouse_moved(const Event::MouseMoved& evt) {
    if (m_launched)
        return;

    float size_square = (float)std::min(m_scene->width(), m_scene->height());

    float offset_x = (m_scene->width() - size_square) / size_square;
    float offset_y = (m_scene->height() - size_square) / size_square;

    float rel_mx = 1.0f - 2.0f * evt.x / size_square;
    float rel_my = 1.0f - 2.0f * evt.y / size_square;

    m_sphere_preview->position = glm::vec3(rel_mx+offset_x, 0.0f, rel_my+offset_y);
}


// -- Drawing helper --
// circles
std::shared_ptr<Circle> TestCommander::draw_circle(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, vec4& color) {
    return scene->addCircle(std::make_shared<Circle>(pos, radius, color));
}
std::shared_ptr<Circle> TestCommander::draw_circle_dead(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, vec4& color) {
    auto circle = draw_circle(scene, pos, radius, color);
    Physx::Add(circle, Physx::BodyType::Static);
    return circle;
}
std::shared_ptr<Circle> TestCommander::draw_circle_alive(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, vec4& color) {
    auto circle = draw_circle(scene, pos, radius, color);
    Physx::Add(circle, Physx::BodyType::Dynamic);
    return circle;
}

// lines
std::shared_ptr<Line> TestCommander::draw_line(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, vec4& color) {
    return scene->addLine(std::make_shared<Line>(pos_start, pos_end, color));
}
std::shared_ptr<Line> TestCommander::draw_line_dead(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, vec4& color) {
    auto line = draw_line(scene, pos_start, pos_end, color);
    Physx::Add(line, Physx::BodyType::Static);
    return line;
}
std::shared_ptr<Line> TestCommander::draw_line_alive(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, vec4& color) {
    auto line = draw_line(scene, pos_start, pos_end, color);
    Physx::Add(line, Physx::BodyType::Dynamic);
    return line;
}

