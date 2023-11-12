#pragma once

#include <memory>
#include <queue>

#include "../Engine/Graphic/BaseScene.hpp"

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
        std::queue<int> keyPressed = {};
    };

    static ActionCode UpdateState(Game::State& state);
    static std::unique_ptr<BaseScene> Game::MakeScene();

private:
    static Game& _get();
    ActionCode _validateState(const Game::State& state);

    struct _HiddenGameState {
        Game::State previous;
    } m_state;
	
    // No copy with private builder pattern
    Game() = default;

    Game& operator=(const Game&) = delete;
    Game(const Game&)            = delete;
    Game(Game&&)                 = delete;
};