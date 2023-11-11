#include <iostream>
#include <string>
#include <vector>

#include "Engine/Graphic/Window.hpp"

#include "Game/Game.hpp"
#include "Game/Scene/TestScene.hpp"

#include "Game/Scene/FruitScene.hpp"
#include "Game/Scene/SlimeScene.hpp"
#include "Game/Scene/CrashScene.hpp"
#include "Game/Scene/FlapiScene.hpp"

// -- Entry point --
int main() {
    // Create window
    Window window(1600, 900, "The Game");

    // Open menu
    window.scene(std::make_unique<SlimeScene>());

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

                // All scene
                case GLFW_KEY_1:
                    window.scene(std::make_unique<FruitScene>());
                    break;

                case GLFW_KEY_2:
                    window.scene(std::make_unique<SlimeScene>());
                    break;

                case GLFW_KEY_3:
                    window.scene(std::make_unique<CrashScene>());
                    break;

                case GLFW_KEY_4:
                    window.scene(std::make_unique<FlapiScene>());
                    break;

                case GLFW_KEY_5:
                    window.scene(std::make_unique<TestScene>());
                    break;
            }
        }

        // Compute physics before redrawing
        Game::UpdateState(gamestate);

    } while (window.update());

    // Clean up
    return 0;
}