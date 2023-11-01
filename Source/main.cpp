#include <iostream>
#include <string>

#include "Engine/Graphic/Shader.hpp"
#include "Engine/Graphic/BaseScene.hpp"
#include "Engine/Graphic/Window.hpp"
#include "Engine/Graphic/TextEngine.hpp"

#include "Game/Scene/SimpleScene.hpp"

// -- Entry point --
int main() {
    // Create window
    Window window(800, 600, "The Game");

    // Create scene to be displayed
    window.scene = std::make_unique<SimpleScene>();

    // Main loop
    do {
        // Read keyboard inputs
        for (auto key : window.keyPressed()) {
            switch (key) {
                case GLFW_KEY_ESCAPE: 
                    window.close(); 
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