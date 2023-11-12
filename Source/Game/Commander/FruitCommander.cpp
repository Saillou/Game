#include "FruitCommander.hpp"

#include <iostream>

// Events
void FruitCommander::_on_key_pressed(const Event::KeyPressed& evt) {
    std::cout << "FruitCommander::OnKeyPressed: " << evt.key << std::endl;
}
