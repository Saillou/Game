#include "TestCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"
#include "../../Utils/Timer.hpp"

using namespace glm;


// Instance
TestCommander::TestCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_last_add_ms(Timer::GetCurrentTime<Timer::millisecond>()),
    m_scene(std::dynamic_pointer_cast<TestScene>(scene))
{
    // Context 2d
    m_sphere_preview = draw_circle(m_scene, vec2(1.0f, 1.0f), 0.10f,  vec4(0.0f, 0.0f, 1.0f, 1.0f));
    
    float size = 0.75f;
    const vec2 A(-size, -size);
    const vec2 B(-size, +size);
    const vec2 C(+size, +size);
    const vec2 D(+size, -size);
    const vec4 yellow(1.0f, 1.0f, 0.0f, 1.0f);

    //draw_circle_dead(m_scene, vec2(0, 0), 0.20f, yellow);
    //draw_line_dead(m_scene, A, B, yellow);
    //draw_line_alive(m_scene, B, C, yellow);
    //draw_line_dead(m_scene, C, D, yellow);
    draw_line_dead(m_scene, vec2(-1.0f, 0.0f), vec2(+1.0f, 0.0f), yellow);
    //draw_line_dead(m_scene, D*0.25f, B*0.5f, yellow);
}

// Events
void TestCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    const int DELAY_MS_ADD = 300; //ms

    // React to the emitted keys 
    if (evt.key == Key::Space) {
        int64_t current_time = Timer::GetCurrentTime<Timer::millisecond>();
        if (current_time - m_last_add_ms > DELAY_MS_ADD)
        {
            m_last_add_ms = current_time;
            draw_circle_alive(m_scene, vec2(-m_sphere_preview->position.x, m_sphere_preview->position.z), 0.10f, vec4(0.0f, 0.0f, 1.0f, 1.0f));
        }
    }

    if (evt.key == Key::ArrowLeft) {

    }

    if (evt.key == Key::ArrowRight) {

    }
}

void TestCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    float size_square = (float)std::min(m_scene->width(), m_scene->height());

    float offset_x = (m_scene->width() - size_square) / size_square;
    float offset_y = (m_scene->height() - size_square) / size_square;

    float rel_mx = 1.0f - 2.0f * evt.x / size_square;
    float rel_my = 1.0f - 2.0f * evt.y / size_square;

    m_sphere_preview->position = vec3(rel_mx+offset_x, 0.0f, rel_my+offset_y);
}


// -- Drawing helper --
// circles
std::shared_ptr<Circle> TestCommander::draw_circle(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, const vec4& color) {
    return scene->addCircle(std::make_shared<Circle>(pos, radius, color));
}
std::shared_ptr<Circle> TestCommander::draw_circle_dead(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, const vec4& color) {
    auto circle = draw_circle(scene, pos, radius, color);
    Physx::Add(circle, Physx::BodyType::Static);
    return circle;
}
std::shared_ptr<Circle> TestCommander::draw_circle_alive(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, const vec4& color) {
    auto circle = draw_circle(scene, pos, radius, color);
    Physx::Add(circle, Physx::BodyType::Dynamic);
    return circle;
}

// lines
std::shared_ptr<Line> TestCommander::draw_line(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, const vec4& color) {
    return scene->addLine(std::make_shared<Line>(pos_start, pos_end, color));
}
std::shared_ptr<Line> TestCommander::draw_line_dead(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, const vec4& color) {
    auto line = draw_line(scene, pos_start, pos_end, color);
    Physx::Add(line, Physx::BodyType::Static);
    return line;
}
std::shared_ptr<Line> TestCommander::draw_line_alive(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, const vec4& color) {
    auto line = draw_line(scene, pos_start, pos_end, color);
    Physx::Add(line, Physx::BodyType::Dynamic);
    return line;
}

