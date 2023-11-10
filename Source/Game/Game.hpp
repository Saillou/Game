#pragma once

// Data
struct GameState {
    bool isJumping;
};

// Singleton
class Game {
    Game() = default;

    struct _HiddenGameState {
        GameState previous;
    } m_state;

    bool validateState(const GameState& state);
    static Game& _get();
	
public:
    static void UpdateState(GameState& state);
    ~Game() = default;

    Game& operator=(const Game&) = delete;
    Game(const Game&)            = delete;
    Game(Game&&)                 = delete;
};