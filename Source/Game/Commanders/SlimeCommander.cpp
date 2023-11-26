#include "SlimeCommander.hpp"

#include "../../Engine/Events/Common.hpp"

using namespace glm;

// ------------ Helpers ------------
static const auto reset_cam = [&](std::shared_ptr<SlimeScene> scene) {
    scene->camera().position = glm::vec3(0.0f, 3.8f, +0.5f);
    scene->camera().direction = glm::vec3(0.0f, 0.0f, +0.5f);
    scene->camera().fieldOfView = 45.0f;
    scene->camera().lookAt(glm::vec3(0, 0, 1));

    if (scene->enable_2d_camera)
        scene->camera().useOrtho(scene->width() / (float)scene->height());
    else
        scene->camera().usePerspective(scene->width() / (float)scene->height());
};

static const auto get_cam_angles = [&](std::shared_ptr<SlimeScene> scene) {
    float theta_x = asin(scene->camera().position.x / 3.8f);
    float theta_z = asin(scene->camera().position.z / 3.8f);
    float theta_y = theta_x + theta_z;

    return glm::vec3(theta_x, theta_y, theta_z);
};

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
    // Timer
    float t_sec = m_time.elapsed<Timer::millisecond>() / 1000.0f;

    // Get state
    m_game->update(t_sec, ([=]() -> SlimeScene::State {
        auto curr_state = m_scene->state;

        // The end
        if (curr_state == SlimeScene::State::Ending)
            return SlimeScene::State::Ending;

        // Next
        SlimeScene::State next_state = (SlimeScene::State)(curr_state + 1);
        
        auto it_next = SlimeScene::StartTime.find(next_state);
        if (it_next != SlimeScene::StartTime.cend() && it_next->second < t_sec)
            return next_state;

        // Nothing to do
        return curr_state;
    })());
}

void SlimeCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    switch (evt.key) {
        case Key::ArrowRight:   _on_key_right();    break;
        case Key::ArrowLeft:    _on_key_left();     break;
        case Key::ArrowUp:      _on_key_up();       break;
        case Key::ArrowDown:    _on_key_down();     break;
        case Key::Space:        _on_key_space();    break;
    }

    // 2D world
    if (evt.key == 'C') {
        m_scene->enable_2d_camera = true;
        m_scene->lightning(false);
        reset_cam(m_scene);
    }

    // 3D world
    if (evt.key == 'V') {
        m_scene->enable_2d_camera = false;
        m_scene->lightning(true);
        reset_cam(m_scene);
    }

    // Other shortcut
    if (evt.key == 'R') {
        Event::Emit(CustomEvents::SceneRefresh());
    }
}

void SlimeCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}

// Private
void SlimeCommander::_on_key_left() {
    // --- Intro ---
    if (m_scene->state == SlimeScene::Intro) {
        return;
    }

    // --- Game ---
    m_game->player.move(vec3(+1.0f, 0, 0));
}

void SlimeCommander::_on_key_right() {
    // --- Intro ---
    if (m_scene->state == SlimeScene::Intro) {
        return;
    }

    // --- Game ---
    m_game->player.move(vec3(-1.0f, 0, 0));
}


void SlimeCommander::_on_key_up() {
    // --- Intro ---
    if (m_scene->state == SlimeScene::Intro) {
        return;
    }

    // --- 2D ---
    if (m_scene->state == SlimeScene::Game2D) {
        return;
    }

    // --- Game ---
    m_game->player.move(vec3(0, -1.0f, 0));
}
void SlimeCommander::_on_key_down() {
    // --- Intro ---
    if (m_scene->state == SlimeScene::Intro) {
        return;
    }

    // --- 2D ---
    if (m_scene->state == SlimeScene::Game2D) {
        return;
    }

    // --- Game ---
    m_game->player.move(vec3(0, +1.0f, 0));
}

void SlimeCommander::_on_key_space() {
    // --- Intro ---
    if (m_scene->state == SlimeScene::Intro) {
        return;
    }


    // --- Game ---
    m_game->player.jump();
}