#pragma once

#include "../../Engine/Physx/Physx.hpp"
#include "../../Engine/Graphic/Base/BaseCommander.hpp"
#include "../Scenes/CrashScene.hpp"

struct CrashCommander : public BaseCommander {
    CrashCommander(std::shared_ptr<BaseScene> scene);

protected:
    // Events
    void _on_key_pressed(const CustomEvents::KeyPressed& evt) override;
    void _on_mouse_moved(const CustomEvents::MouseMoved& evt) override;

private:
    // Members
    std::shared_ptr<CrashScene> m_scene;
};