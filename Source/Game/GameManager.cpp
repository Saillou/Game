#include "GameManager.hpp"

#include "../Engine/Events/CustomEvents.hpp"

#include "Commanders/IntroCommander.hpp"
#include "Commanders/SlimeCommander.hpp"
#include "Commanders/EndingCommander.hpp"

// Private
GameManager::GameManager() {
	_subscribe(&GameManager::_on_scene_refresh);
	_subscribe(&GameManager::_on_scene_ended);
}

GameManager::ActionCode GameManager::_validateState(GameManager::State& state) {
	bool desireToChange = _curr_state.sceneDesired != SceneId::None;

	if (desireToChange)
		state.sceneId = _curr_state.sceneDesired;
	
	if (desireToChange || state.sceneId != _curr_state.sceneId)
		return ActionCode::Refresh;

	return ActionCode::Ok;
}

void GameManager::_on_scene_refresh(const CustomEvents::SceneRefresh& evt) {
	_curr_state.sceneDesired = _curr_state.sceneId;
}

void GameManager::_on_scene_ended(const CustomEvents::SceneEnded& evt) {
	_curr_state.sceneDesired = (SceneId)(_curr_state.sceneId + 1);
}

GameManager& GameManager::_get() {
	static GameManager game;
	return game;
}

// Public (static)
GameManager::ActionCode GameManager::UpdateState(GameManager::State& state) {
	GameManager& game = _get();

	// Emit events
	Event::Emit(CustomEvents::UpdateGameState());

	while (!state.keyPressed.empty()) {
		int key = state.keyPressed.front();
		state.keyPressed.pop();

		Event::Emit(CustomEvents::KeyPressed(key));
	}

	if (game._curr_state.mousePos != state.mousePos) {
		Event::Emit(CustomEvents::MouseMoved((int)state.mousePos.x, (int)state.mousePos.y));
	}

	// Stop/Refresh here, invalid state detected
	ActionCode action = game._validateState(state);

	game._curr_state = state;
	return action;
}

void GameManager::Refresh(Window& window) {
	GameManager& game = _get();

	// Change view
	window.scene(([&]() -> std::shared_ptr<BaseScene> {
		switch (game._curr_state.sceneId) 
		{
			case SceneId::Intro:	return std::make_shared<IntroScene>();
			case SceneId::Slime:	return std::make_shared<SlimeScene>();
			case SceneId::Ending:	return std::make_shared<EndingScene>();

			default: 
				return std::make_shared<BaseScene>();
		}})()
	);

	// Change commander
	game._commander = ([&]() -> std::unique_ptr<BaseCommander> {
		switch (game._curr_state.sceneId) 
		{
			case SceneId::Intro:	return std::make_unique<IntroCommander>(window.scene());
			case SceneId::Slime:	return std::make_unique<SlimeCommander>(window.scene());
			case SceneId::Ending:	return std::make_unique<EndingCommander>(window.scene());

			default:
				return std::make_unique<BaseCommander>(window.scene());
		}
	})();

	// Change sound
	switch (game._curr_state.sceneId)
	{
		case SceneId::Intro:  SoundPlayer::PlayLoop("Resources/Intro.wav"); break;
		case SceneId::Slime:  SoundPlayer::PlayLoop("Resources/Slime.wav"); break;
		case SceneId::Ending: SoundPlayer::PlayLoop("Resources/Intro.wav"); break;
	}
}
