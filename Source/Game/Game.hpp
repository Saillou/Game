#pragma once

#include <memory>
#include <queue>

#include "../Engine/Graphic/Window.hpp"
#include "../Engine/Graphic/Base/BaseCommander.hpp"

// Data
enum class SceneId {
    None = -1, Other = 0, 
    FruitScene, SlimeScene, CrashScene, FlapiScene
};

// Singleton
class Game {
public:
    enum class ActionCode {
        Close = 0, Ok, Refresh
    };

    struct State {
        SceneId sceneId = SceneId::None;
        glm::vec2 mousePos = {};
        std::queue<int> keyPressed = {};
    };

    static ActionCode UpdateState(Game::State& state);
    static void Refresh(Window& window);

private:
    static Game& _get();

    // Instance members
    Game::State _curr_state;
    std::unique_ptr<BaseCommander> _commander;

    ActionCode _validateState(const Game::State& state);
	
    // -- No copy --
    Game() = default;

    Game& operator=(const Game&) = delete;
    Game(const Game&)            = delete;
    Game(Game&&)                 = delete;
};