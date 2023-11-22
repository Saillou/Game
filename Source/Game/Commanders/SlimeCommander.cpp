#include "SlimeCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"
#include "../../Utils/Timer.hpp"

using namespace glm;


// Instance
SlimeCommander::SlimeCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<SlimeScene>(scene))
{
    // ..
}

// Events
void SlimeCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // ..
}

void SlimeCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
