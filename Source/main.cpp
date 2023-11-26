#include <string>

#include "Game/GameManager.hpp"
#include "Utils/Timer.hpp"
#include "Engine/Physx/Physx.hpp"
#include "Engine/Graphic/Window.hpp"

// Options
const bool FullScreen = 
#ifdef _DEBUG
        false;
#else
        true;
#endif

// -- Entry point --
int main() {
    // Create window
    GameManager::State gamestate;
    Window window(1600, 900, "The Game", FullScreen);

    // Main loop
    gamestate.sceneId = SceneId::Intro;

    Timer::Chronometre chrono;
    do {
        // Read keyboard inputs
        for (auto key : window.keyPressed()) {
            switch (key) {
                // Window control
                case GLFW_KEY_ESCAPE: 
                    window.close(); 
                    break;

                case GLFW_KEY_F11:
                    window.toggleFullScreen();
                    break;

                // Change scene
                case GLFW_KEY_1: gamestate.sceneId = SceneId::Intro;     break;
                case GLFW_KEY_2: gamestate.sceneId = SceneId::Slime;     break;
                case GLFW_KEY_3: gamestate.sceneId = SceneId::Ending;    break;

                // Game inputs
                default:
                    gamestate.keyPressed.push(key);
                    break;
            }
        }

        // Read mouse
        gamestate.mousePos = window.mousePos();

        // Compute world
        switch (GameManager::UpdateState(gamestate)) {
            // Let's update
            case GameManager::ActionCode::Ok:
                Physx::Compute(chrono.elapsed<Timer::microsecond>()/1000.0f);
                chrono.tic();
                break;

            // Create (or change) the scene
            case GameManager::ActionCode::Refresh:
                GameManager::Refresh(window);
                break;

            // Stop
            case GameManager::ActionCode::Close:
                window.close();
                break;
        }
    } while (window.update());

    // Clean up
    return 0;
}