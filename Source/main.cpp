#include <iostream>
#include <string>
#include <vector>

#include "Engine/Graphic/Window.hpp"

#include "Game/Scene/ExperimentalScene.hpp"
#include "Game/Scene/TesselScene.hpp"

// -- Entry point --
int main() {
    // Create window
    Window window(1024, 768, "The Game");
    window.scene(std::make_unique<TesselScene>());

    // Main loop
    do {
        // Read keyboard inputs
        for (auto key : window.keyPressed()) {
            switch (key) {
                case GLFW_KEY_ESCAPE: 
                    window.close(); 
                    break;

                case GLFW_KEY_SPACE: // change scene
                    window.scene(std::make_unique<ExperimentalScene>());
                    break;

                default: 
                    break;
            }
        }

        // Update game state
        // ..

        // Compute physics before redrawing
        // ..
    } while (window.update());

    // Clean up
    return 0;
}