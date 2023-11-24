#pragma once

#include "../../Engine/Physx/Physx.hpp"
#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scenes/EndingScene.hpp"

struct EndingCommander : public BaseCommander {
    EndingCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_key_pressed(const CustomEvents::KeyPressed& evt) override;
    void _on_mouse_moved(const CustomEvents::MouseMoved& evt) override;

private:
    // Members
    std::shared_ptr<EndingScene> m_scene;
};