#include "IntroCommander.hpp"
#include <glm/gtx/string_cast.hpp>

#include "../../Engine/Physx/Physx.hpp"

using namespace glm;


// Instance
IntroCommander::IntroCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_scene(std::dynamic_pointer_cast<IntroScene>(scene))
{
    // ..
}

void IntroCommander::_on_game_state_update(const CustomEvents::UpdateGameState& evt) {
    float t = m_time.elapsed<Timer::millisecond>() / 1000.0f;
    Camera& cam = m_scene->camera();

    if (t == 0.0f) {
        cam.position = glm::vec3(0.0f, 2.0f, 0.0f);
        cam.direction = glm::vec3(0.0f, 0.0, 0.0f);
        cam.fieldOfView = 45.0f;
    }
    else if (t < 5.0f) {
        cam.position += glm::vec3(cos(t) / 5.0f, sin(t) / 3.0f, sin(t) / 7.0f);
        cam.direction = 1.0f * glm::vec3(cos(t*0.3f), sin(t*0.5f), sin(t*0.7f));

        m_scene->startText();
    }
    else if (t < 7.0f) {
        cam.position *= 0.95f;
        cam.direction *= 0.95f;
    }
    else if (t < 8.0f) {
        m_scene->startBrownian();
    }
    else {
        Event::Emit(CustomEvents::SceneEnded());
    }
}

// Events
void IntroCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // ..
}

void IntroCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
