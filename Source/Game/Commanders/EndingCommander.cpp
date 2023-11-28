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
    // ..
}

// Events
void EndingCommander::_on_game_state_update(const CustomEvents::UpdateGameState& evt) {
    // ..
}

void EndingCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // ..
}

void EndingCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
