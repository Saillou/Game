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

void IntroCommander::_on_game_state_update(const CustomEvents::UpdateGameState& evt) {
    static float a = 0.0f;
    a += 0.01f;

    //if (a >= 3.0f)
    //    m_ended = true;

    m_scene->camera().position += glm::vec3(cos(a)/5.0f, sin(a)/3.0f, sin(a)/7.0f);
    m_scene->camera().direction = glm::vec3(0.0f, 0.0f, 0.0f);
    m_scene->camera().fieldOfView = 45.0f;
    m_scene->camera().lookAt(glm::vec3(0, 0, 1));
}

// Events
void IntroCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // ..
}

void IntroCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
