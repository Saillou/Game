#include "CrashCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"
#include "../../Utils/Timer.hpp"

using namespace glm;


// Instance
CrashCommander::CrashCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<CrashScene>(scene))
{
    // ..
}

// Events
void CrashCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // ..
}

void CrashCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
