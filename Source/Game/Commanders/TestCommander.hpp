#pragma once

#include "../../Engine/Physx/Physx.hpp"
#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scenes/TestScene.hpp"

#include <unordered_map>
#include <optional>

struct TestCommander : public BaseCommander {
    TestCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_key_pressed(const CustomEvents::KeyPressed& evt) override;
    void _on_mouse_moved(const CustomEvents::MouseMoved& evt) override;

private:
    // Drawing helpers
    std::shared_ptr<Circle> static draw_circle(std::shared_ptr<TestScene>, const glm::vec2& pos, const float radius, const glm::vec4& color, std::optional<Physx::BodyType> = {});
    std::shared_ptr<Line> static draw_line(std::shared_ptr<TestScene>, const glm::vec2& pos_start, const glm::vec2& pos_end, const glm::vec4& color, std::optional<Physx::BodyType> = {});

    // Members
    std::shared_ptr<TestScene> m_scene;

    int64_t m_last_add_ms;
    std::unordered_map<std::string, std::shared_ptr<Line>> m_lines;
    std::unordered_map<std::string, std::shared_ptr<Circle>> m_circles;

    std::shared_ptr<Circle> m_sphere_preview;
};