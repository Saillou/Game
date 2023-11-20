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

    draw_circle(m_scene, vec2(0, 0), 0.20f, yellow, Physx::BodyType::Static);
    draw_line(m_scene, A, B, yellow, Physx::BodyType::Static);
    draw_line(m_scene, B, C, yellow, Physx::BodyType::Static);
    draw_line(m_scene, C, D, yellow, Physx::BodyType::Static);
    draw_line(m_scene, D, A, yellow, Physx::BodyType::Static);
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

            const vec2 last_pos(
                -m_sphere_preview->position.x, 
                m_sphere_preview->position.z
            );
            draw_circle(m_scene, last_pos, 0.10f, vec4(0.0f, 0.0f, 1.0f, 1.0f), Physx::BodyType::Dynamic);
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
std::shared_ptr<Circle> TestCommander::draw_circle(std::shared_ptr<TestScene> scene, const vec2& pos, const float radius, const vec4& color, std::optional<Physx::BodyType> type) {
    auto circle = scene->addCircle(std::make_shared<Circle>(pos, radius, color));
    if(type.has_value())
        Physx::Add(circle, type.value());
    return circle;
}

// lines
std::shared_ptr<Line> TestCommander::draw_line(std::shared_ptr<TestScene> scene, const vec2& pos_start, const vec2& pos_end, const vec4& color, std::optional<Physx::BodyType> type) {
    auto line = scene->addLine(std::make_shared<Line>(pos_start, pos_end, color));
    if (type.has_value())
        Physx::Add(line, type.value());
    return line;
}