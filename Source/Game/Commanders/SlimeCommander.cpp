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
    m_game->player.update();
    m_game->target.update();
}

void SlimeCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    switch (evt.key) {
        case Key::ArrowRight:
            m_game->player.move(vec3(-1.0f, 0, 0));
            break;

        case Key::ArrowLeft:
            m_game->player.move(vec3(+1.0f, 0, 0));
            break;

        case Key::Space:
            m_game->player.jump();
            break;
    }

    // -- Camera movements -- 
    static const auto reset_cam = [&]() {
        m_scene->camera().position  = glm::vec3(0.0f, 3.8f, +0.5f);
        m_scene->camera().direction = glm::vec3(0.0f, 0.0f, +0.5f);
        m_scene->camera().fieldOfView = 45.0f;
        m_scene->camera().lookAt(glm::vec3(0, 0, 1));

        if (m_scene->enable_2d_camera)
            m_scene->camera().useOrtho(m_scene->width() / (float)m_scene->height());
        else
            m_scene->camera().usePerspective(m_scene->width() / (float)m_scene->height());
    };

    static const auto get_cam_angles = [&]() {
        float theta_x = asin(m_scene->camera().position.x / 3.8f);
        float theta_z = asin(m_scene->camera().position.z / 3.8f);
        float theta_y = theta_x + theta_z;

        return glm::vec3(theta_x, theta_y, theta_z);
    };


    // -- 
    constexpr float speed_cam = 0.04f;
    const glm::vec3 angles = get_cam_angles();

    if (evt.key == Key::ArrowLeft) {
        if (m_scene->enable_2d_camera) {
            m_scene->camera().position += glm::vec3(speed_cam, 0.0f, 0.0f);
            m_scene->camera().direction += glm::vec3(speed_cam, 0.0f, 0.0f);
        }
        else {
            m_scene->camera().position = 3.8f * glm::vec3(
                sin(glm::clamp(angles.x - speed_cam, -1.0f, +1.0f)),
                cos(glm::clamp(angles.y - speed_cam, -1.0f, +1.0f)),
                sin(angles.z)
            );
        }
    }

    if (evt.key == Key::ArrowRight) {
        if (m_scene->enable_2d_camera) {
            m_scene->camera().position -= glm::vec3(speed_cam, 0.0f, 0.0f);
            m_scene->camera().direction -= glm::vec3(speed_cam, 0.0f, 0.0f);
        }
        else {
            m_scene->camera().position = 3.8f * glm::vec3(
                sin(glm::clamp(angles.x + speed_cam, -1.0f, +1.0f)),
                cos(glm::clamp(angles.y + speed_cam, -1.0f, +1.0f)),
                sin(angles.z)
            );
        }
    }

    // 2D world
    if (evt.key == 'C') {
        m_scene->enable_2d_camera = true;
        m_scene->lightning(false);
        reset_cam();
    }

    // 3D world
    if (evt.key == 'V') {
        m_scene->enable_2d_camera = false;
        m_scene->lightning(true);
        reset_cam();
    }
}

void SlimeCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // ..
}
