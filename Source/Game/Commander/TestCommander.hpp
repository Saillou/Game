#pragma once

#include "../../Engine/Graphic/Base/BaseCommander.hpp"

#include "../Scene/TestScene.hpp"
#include <unordered_map>

struct TestCommander : public BaseCommander {
    TestCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_key_pressed(const Event::KeyPressed& evt) override;
    void _on_mouse_moved(const Event::MouseMoved& evt) override;

private:
    // Drawing helpers
    std::shared_ptr<Circle> static draw_circle(std::shared_ptr<TestScene>, const glm::vec2& pos, const float radius, glm::vec4& color);
    std::shared_ptr<Circle> static draw_circle_dead(std::shared_ptr<TestScene>, const glm::vec2& pos, const float radius, glm::vec4& color);
    std::shared_ptr<Circle> static draw_circle_alive(std::shared_ptr<TestScene>, const glm::vec2& pos, const float radius, glm::vec4& color);

    std::shared_ptr<Line> static draw_line(std::shared_ptr<TestScene>, const glm::vec2& pos_start, const glm::vec2& pos_end, glm::vec4& color);
    std::shared_ptr<Line> static draw_line_dead(std::shared_ptr<TestScene>, const glm::vec2& pos_start, const glm::vec2& pos_end, glm::vec4& color);
    std::shared_ptr<Line> static draw_line_alive(std::shared_ptr<TestScene>, const glm::vec2& pos_start, const glm::vec2& pos_end, glm::vec4& color);

    // Members
    std::shared_ptr<TestScene> m_scene;

    bool m_launched = false;
    std::unordered_map<std::string, std::shared_ptr<Line>> m_lines;
    std::unordered_map<std::string, std::shared_ptr<Circle>> m_circles;

    std::shared_ptr<Circle> m_sphere_preview;
};