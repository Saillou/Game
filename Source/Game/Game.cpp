#include "Game.hpp"

#include "../Engine/Events/CustomEvents.hpp"

#include "Commanders/TestCommander.hpp"
#include "Commanders/IntroCommander.hpp"
#include "Commanders/SlimeCommander.hpp"
#include "Commanders/CrashCommander.hpp"
#include "Commanders/EndingCommander.hpp"

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

	// Next scene
	if (game._commander && game._commander->ended()) {
		state.sceneId = SceneId((int)game._curr_state.sceneId + 1);
	}

	// Stop/Refresh here, invalid state detected
	ActionCode action = game._validateState(state);
	if (action == ActionCode::Refresh)
		goto Result;

	// Emit events
	while (!state.keyPressed.empty()) {
		int key = state.keyPressed.front();
		state.keyPressed.pop();

		Event::Emit(CustomEvents::KeyPressed(key));
	}

	if (game._curr_state.mousePos != state.mousePos) {
		Event::Emit(CustomEvents::MouseMoved((int)state.mousePos.x, (int)state.mousePos.y));
	}

Result:
	game._curr_state = state;
	Event::Emit(CustomEvents::UpdateGameState());
	return action;
}

void Game::Refresh(Window& window) {
	Game& game = _get();

	// Change view
	window.scene(([&]() -> std::shared_ptr<BaseScene> {
		switch (game._curr_state.sceneId) 
		{
			case SceneId::TestScene:	return std::make_shared<TestScene>();
			case SceneId::Intro:		return std::make_shared<IntroScene>();
			case SceneId::Slime:		return std::make_shared<SlimeScene>();
			case SceneId::Crash:		return std::make_shared<CrashScene>();
			case SceneId::Ending:		return std::make_shared<EndingScene>();

			default: 
				return std::make_shared<BaseScene>();
		}})()
	);

	// Change commander
	game._commander = ([&]() -> std::unique_ptr<BaseCommander> {
		switch (game._curr_state.sceneId) 
		{
			case SceneId::TestScene:	return std::make_unique<TestCommander>(window.scene());
			case SceneId::Intro:		return std::make_unique<IntroCommander>(window.scene());
			case SceneId::Slime:		return std::make_unique<SlimeCommander>(window.scene());
			case SceneId::Crash:		return std::make_unique<CrashCommander>(window.scene());
			case SceneId::Ending:		return std::make_unique<EndingCommander>(window.scene());

			default:
				return std::make_unique<BaseCommander>(window.scene());
		}
	})();
}
