#include "BaseCommander.hpp"

#include <iostream>

BaseCommander::BaseCommander(std::shared_ptr<BaseScene> scene) : m_scene(scene) {
    // Root events
    _subscribe(&BaseCommander::_on_key_pressed);
}

void BaseCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    std::cout << "BaseCommander::OnKeyPressed: " << evt.key << std::endl;

    // Test camera position/direction
    const float speed = 0.01f;

    switch (evt.key) {
        // Move camera
        case Key::ArrowLeft: 
            m_scene->moveCameraPosition(+speed, 0, 0); 
            break;

        case Key::ArrowRight: 
            m_scene->moveCameraPosition(-speed, 0, 0); 
            break;

        case Key::ArrowUp:
            m_scene->moveCameraPosition(0, +speed, 0);
            break;

        case Key::ArrowDown:
            m_scene->moveCameraPosition(0, -speed, 0);
            break;

        case 'O':
            m_scene->moveCameraPosition(0, 0, +speed);
            break;

        case 'P':
            m_scene->moveCameraPosition(0, 0, -speed);
            break;


        // Move direction
        case 'A':
            m_scene->moveCameraDirection(+speed, 0, 0);
            break;

        case 'D':
            m_scene->moveCameraDirection(-speed, 0, 0);
            break;

        case 'W':
            m_scene->moveCameraDirection(0, +speed, 0);
            break;

        case 'S':
            m_scene->moveCameraDirection(0, -speed, 0);
            break;

        case 'Q':
            m_scene->moveCameraDirection(0, 0, +speed);
            break;

        case 'E':
            m_scene->moveCameraDirection(0, 0, -speed);
            break;


        // Change Fov
        case 'C':
            m_scene->changeCameraPerspective(+speed*10);
            break;

        case 'V':
            m_scene->changeCameraPerspective(-speed*10);
            break;
    }
}