#include <iostream>
#include <string>
#include <vector>

#include "Engine/Graphic/Window.hpp"
#include "Game/Scene/FruitScene.hpp"
#include "Game/Scene/TesselScene.hpp"
#include "Game/Game.hpp"

// -- Entry point --
int main() {
    // Create window
    Window window(1024, 768, "The Game");
    window.scene(std::make_unique<TesselScene>());

    // Main loop
    GameState gamestate;

    do {
        // Read keyboard inputs
        for (auto key : window.keyPressed()) {
            switch (key) {
                case GLFW_KEY_ESCAPE: 
                    window.close(); 
                    break;

                case GLFW_KEY_SPACE:
                    gamestate.spacePressed = true;
                    break;

                default: 
                    break;
            }
        }

        // Compute physics before redrawing
        Game::UpdateState(gamestate);

    } while (window.update());

    // Clean up
    return 0;
}