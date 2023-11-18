#pragma once

#include "../../Engine/Graphic/Base/BaseCommander.hpp"

#include "../Scene/TestScene.hpp"

struct TestCommander : public BaseCommander {
    TestCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_key_pressed(const Event::KeyPressed& evt) override;
    void _on_mouse_moved(const Event::MouseMoved& evt) override;

private:
    // Drawing helpers
    void static draw_circle(std::shared_ptr<TestScene>, const glm::vec2& pos, const float radius, glm::vec4& color);
    void static draw_circle_dead(std::shared_ptr<TestScene>, const glm::vec2& pos, const float radius, glm::vec4& color);
    void static draw_circle_alive(std::shared_ptr<TestScene>, const glm::vec2& pos, const float radius, glm::vec4& color);

    void static draw_line(std::shared_ptr<TestScene>, const glm::vec2& pos_start, const glm::vec2& pos_end, glm::vec4& color);
    void static draw_line_dead(std::shared_ptr<TestScene>, const glm::vec2& pos_start, const glm::vec2& pos_end, glm::vec4& color);
    void static draw_line_alive(std::shared_ptr<TestScene>, const glm::vec2& pos_start, const glm::vec2& pos_end, glm::vec4& color);

    // Members
    std::shared_ptr<TestScene> m_scene;
};