#include "EndingCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"
#include "../../Utils/Timer.hpp"

using namespace glm;


// Instance
EndingCommander::EndingCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<EndingScene>(scene))
{
    m_scene->createActors();
}

// Events
void EndingCommander::_on_game_state_update(const CustomEvents::UpdateGameState& evt) {

}

void EndingCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    switch (evt.key) {
    case Key::ArrowRight:   m_scene->moveSlime(-1.0f, 0.f); break;
    case Key::ArrowLeft:    m_scene->moveSlime(+1.0f, 0.f); break;
    case Key::ArrowUp:      m_scene->moveSlime(0.0f, -1.0f); break;
    case Key::ArrowDown:    m_scene->moveSlime(0.0f, +1.0f); break;
    }
}

void EndingCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
