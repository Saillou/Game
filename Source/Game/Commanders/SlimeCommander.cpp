#include "SlimeCommander.hpp"

#include "../../Engine/Events/Common.hpp"

using namespace glm;

// ------------ Instance ------------
SlimeCommander::SlimeCommander(std::shared_ptr<BaseScene> scene):
    BaseCommander(scene),
    m_game(std::make_unique<SlimeGame>()),
    m_scene(std::dynamic_pointer_cast<SlimeScene>(scene))
{
    m_game->useScene(m_scene);
}

SlimeCommander::~SlimeCommander() {
    // for deleting _SlimeGame
}

// Events
void SlimeCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // ..
    switch (evt.key) {
        case Key::ArrowRight:
            m_game->player.move(vec3(+1.0f, 0, 0));
            break;

        case Key::ArrowLeft:
            m_game->player.move(vec3(-1.0f, 0, 0));
            break;

        case Key::Space:
            m_game->player.jump();
            break;
    }
}

void SlimeCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
