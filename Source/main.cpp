#include <string>

#include "Game/Game.hpp"
#include "Utils/Timer.hpp"
#include "Engine/Physx/Physx.hpp"
#include "Engine/Graphic/Window.hpp"

// -- Entry point --
int main() {
    // Create window
    Game::State gamestate;
    Window window(1600, 900, "The Game");

    // Main loop
    gamestate.sceneId = SceneId::Other;
    Timer::Chronometre chrono;
    do {
        // Read keyboard inputs
        for (auto key : window.keyPressed()) {
            switch (key) {
                // Window control
                case GLFW_KEY_ESCAPE: 
                    window.close(); 
                    break;

                // All scenes
                case GLFW_KEY_1: gamestate.sceneId = SceneId::FruitScene; break;
                case GLFW_KEY_2: gamestate.sceneId = SceneId::SlimeScene; break;
                case GLFW_KEY_3: gamestate.sceneId = SceneId::CrashScene; break;
                case GLFW_KEY_4: gamestate.sceneId = SceneId::FlapiScene; break;
                case GLFW_KEY_5: gamestate.sceneId = SceneId::Other;      break;

                // Game inputs
                default:
                    gamestate.keyPressed.push(key);
                    break;
            }
        }

        // Read mouse
        gamestate.mousePos = window.mousePos();

        // Compute world
        switch (Game::UpdateState(gamestate)) {
            // Let's update
            case Game::ActionCode::Ok:
                Physx::Compute(chrono.elapsed<Timer::microsecond>()/1000.0f);
                chrono.tic();
                break;

            // Create (or change) the scene
            case Game::ActionCode::Refresh:
                Game::Refresh(window);
                break;

            // Stop
            case Game::ActionCode::Close:
                window.close();
                break;
        }
    } while (window.update());

    // Clean up
    return 0;
}