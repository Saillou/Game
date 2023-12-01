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

// Events
void SlimeCommander::_on_game_state_update(const CustomEvents::UpdateGameState& evt) {
    float t_sec = m_time.elapsed<Timer::millisecond>() / 1000.0f;

    m_game->update(t_sec, ([=]() -> SlimeGame::State {
        if (m_game->state == SlimeGame::None)
            return SlimeGame::State::Intro;

        if (m_game->state == SlimeGame::Intro && t_sec >= m_game->IntroDuration)
            return SlimeGame::State::Game2D;

        if (m_game->state == SlimeGame::Game2D && m_game->target.body()->position.x <= m_game->Game2DLimit)
            return SlimeGame::State::Game3D;

        if (m_game->state == SlimeGame::State::Game3D && m_game->target.body()->position.x <= m_game->Game3DLimit)
            return SlimeGame::State::BossIntro;

        if (m_game->state == SlimeGame::State::BossIntro && (t_sec - m_game->last_state_change) > m_game->IntroDuration)
            return SlimeGame::State::BossFight;

        if (m_game->state == SlimeGame::State::BossFight && m_game->target.body()->position.z < -0.5f) {
            return 
                m_game->target.body()->position.x < m_game->Game3DLimit ? 
                SlimeGame::State::End : 
                SlimeGame::State::None;
        }

        // Nothing to do
        return m_game->state;
    })());

    // Redo
    if (m_game->state == SlimeGame::State::None)
        Event::Emit(CustomEvents::SceneRefresh());

    // End
    if (m_game->state == SlimeGame::State::End)
        Event::Emit(CustomEvents::SceneEnded());
}

void SlimeCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    switch (evt.key) {
        case Key::ArrowRight:   _on_key_right();    break;
        case Key::ArrowLeft:    _on_key_left();     break;
        case Key::ArrowUp:      _on_key_up();       break;
        case Key::ArrowDown:    _on_key_down();     break;
        case Key::Space:        _on_key_space();    break;
    }

    // Refresh
    if (evt.key == 'R') {
        Event::Emit(CustomEvents::SceneRefresh());
    }
}

void SlimeCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}

// Private
void SlimeCommander::_on_key_left() {
    if (m_game->state == SlimeGame::Intro || m_game->state == SlimeGame::BossIntro)
        return;

    if(m_game->state == SlimeGame::BossFight)
        m_game->player.move(vec3(0, -1.0f, 0));
    else
        m_game->player.move(vec3(+1.0f, 0, 0));
}

void SlimeCommander::_on_key_right() {
    if (m_game->state == SlimeGame::Intro || m_game->state == SlimeGame::BossIntro)
        return;

    if (m_game->state == SlimeGame::BossFight)
        m_game->player.move(vec3(0, +1.0f, 0));
    else
        m_game->player.move(vec3(-1.0f, 0, 0));
}


void SlimeCommander::_on_key_up() {
    if (m_game->state != SlimeGame::Game3D)
        return;

    m_game->player.move(vec3(0, -1.0f, 0));
}
void SlimeCommander::_on_key_down() {
    if (m_game->state != SlimeGame::Game3D)
        return;

    m_game->player.move(vec3(0, +1.0f, 0));
}

void SlimeCommander::_on_key_space() {
    if (m_game->state != SlimeGame::Game2D && m_game->state != SlimeGame::Game3D) 
        return;

    m_game->player.jump();
}