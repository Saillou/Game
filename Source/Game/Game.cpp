#include "Game.hpp"

#include "../Engine/Events/Events.hpp"

#include "Scene/FruitScene.hpp"
#include "Scene/SlimeScene.hpp"
#include "Scene/CrashScene.hpp"
#include "Scene/FlapiScene.hpp"

#include "Scene/TestScene.hpp"

// Private
Game::ActionCode Game::_validateState(const Game::State& state) {
	if (state.sceneId != m_state.previous.sceneId)
		return ActionCode::Refresh;

	return ActionCode::Ok;
}

Game& Game::_get() {
	static Game game;
	return game;
}

// Public (static)
Game::ActionCode Game::UpdateState(Game::State& state) {
	Game& game = _get();

	// Stop/Refresh here, invalid state detected
	ActionCode action = game._validateState(state);
	if (action == ActionCode::Refresh)
		goto Result;

	// Do actions ..
	while (!state.keyPressed.empty()) {
		int key = state.keyPressed.front();
		state.keyPressed.pop();

		Event::Emit(Event::KeyPressed(key));
	}

Result:
	game.m_state.previous = state;
	return action;
}


std::unique_ptr<BaseScene> Game::MakeScene() {
	Game& game = _get();

	switch (game.m_state.previous.sceneId) {
		case SceneId::FruitScene: return std::make_unique<FruitScene>();
		case SceneId::SlimeScene: return std::make_unique<SlimeScene>();
		case SceneId::CrashScene: return std::make_unique<CrashScene>();
		case SceneId::FlapiScene: return std::make_unique<FlapiScene>();

		default: return std::make_unique<TestScene>();
	}
}