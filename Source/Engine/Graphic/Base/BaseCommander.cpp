#include "BaseCommander.hpp"
#include "../../Physx/Physx.hpp"

#include <iostream>

BaseCommander::BaseCommander(std::shared_ptr<BaseScene> scene) : m_scene(scene) {
    // Root events
    _subscribe(&BaseCommander::_on_game_state_update);
    _subscribe(&BaseCommander::_on_key_pressed);
    _subscribe(&BaseCommander::_on_mouse_moved);

    // Clean physx
    Physx::Clear();
}

void BaseCommander::_on_game_state_update(const CustomEvents::UpdateGameState& evt) {
    // To be overrided ..
}

void BaseCommander::_on_key_pressed(const CustomEvents::KeyPressed& evt) {
    // To be overrided ..
    std::cout << "BaseCommander::OnKeyPressed: " << evt.key << std::endl;

    //switch (evt.key) {
    //    // ..
    //}
}

void BaseCommander::_on_mouse_moved(const CustomEvents::MouseMoved& evt) {
    // To be overrided ..
}
