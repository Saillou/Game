#include "IntroCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"
#include "../../Utils/Timer.hpp"

using namespace glm;


// Instance
IntroCommander::IntroCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<IntroScene>(scene))
{
    // ..
}

// Events
void IntroCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // ..
}

void IntroCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
