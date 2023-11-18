#include "Game.hpp"

#include "../Engine/Events/Events.hpp"

// Command
#include "Commander/FruitCommander.hpp"
#include "Commander/SlimeCommander.hpp"
#include "Commander/TestCommander.hpp"

// Scene
#include "Scene/FruitScene.hpp"
#include "Scene/SlimeScene.hpp"
#include "Scene/CrashScene.hpp"
#include "Scene/FlapiScene.hpp"
#include "Scene/TestScene.hpp"

// Private
Game::ActionCode Game::_validateState(const Game::State& state) {
	if (state.sceneId != _curr_state.sceneId)
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

	// Emit events
	while (!state.keyPressed.empty()) {
		int key = state.keyPressed.front();
		state.keyPressed.pop();

		Event::Emit(Event::KeyPressed(key));
	}

	if (game._curr_state.mousePos != state.mousePos) {
		Event::Emit(Event::MouseMoved(state.mousePos.x, state.mousePos.y));
	}

Result:
	game._curr_state = state;
	return action;
}

void Game::Refresh(Window& window) {
	Game& game = _get();

	// Change view
	window.scene(([&]() -> std::shared_ptr<BaseScene> {
		switch (game._curr_state.sceneId) 
		{
			case SceneId::FruitScene: return std::make_shared<FruitScene>();
			case SceneId::SlimeScene: return std::make_shared<SlimeScene>();
			case SceneId::CrashScene: return std::make_shared<CrashScene>();
			case SceneId::FlapiScene: return std::make_shared<FlapiScene>();
			default: 
				return std::make_shared<TestScene>();
		}})()
	);

	// Change commander
	game._commander = ([&]() -> std::unique_ptr<BaseCommander> {
		switch (game._curr_state.sceneId) 
		{
			case SceneId::FruitScene: return std::make_unique<FruitCommander>(window.scene());
			case SceneId::SlimeScene: return std::make_unique<SlimeCommander>(window.scene());
			case SceneId::Other: return std::make_unique<TestCommander>(window.scene());
			default:
				return std::make_unique<BaseCommander>(window.scene());
		}
	})();
}
