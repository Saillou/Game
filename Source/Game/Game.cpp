#include "Game.hpp"

bool Game::validateState(const GameState& state) {
	// .. (state vs m_state.previous)

	return true;
}

Game& Game::_get() {
	static Game game;
	return game;
}

void Game::UpdateState(GameState& state) {
	Game& game = _get();

	// Stop here, invalid state detected
	if (!game.validateState(state))
		return;

	// Do actions ..
	if (state.spacePressed) {

	}

	// Save
	game.m_state.previous = state;

	// Reset
	state.spacePressed = false;
}