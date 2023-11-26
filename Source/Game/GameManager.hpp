#pragma once

#include <memory>
#include <queue>

#include "../Engine/Graphic/Window.hpp"
#include "../Engine/Graphic/Base/BaseCommander.hpp"

// Data
enum SceneId {
    None = -1,
    Intro, Slime, Ending
};

// Singleton
class GameManager : public Event::Subscriber {
public:
    enum class ActionCode {
        Close = 0, Ok, Refresh
    };

    struct State 
    {
        SceneId sceneId = SceneId::None;
        SceneId sceneDesired = SceneId::None;
        glm::vec2 mousePos = {};
        std::queue<int> keyPressed = {};
    };

    static ActionCode UpdateState(GameManager::State& state);
    static void Refresh(Window& window);

private:
    static GameManager& _get();

    // Instance members
    GameManager::State _curr_state;
    std::unique_ptr<BaseCommander> _commander;

    // Instance Methods
    ActionCode _validateState(GameManager::State& state);

    void _on_scene_refresh(const CustomEvents::SceneRefresh& evt);
    void _on_scene_ended(const CustomEvents::SceneEnded& evt);
	
    // -- No copy --
    GameManager();

    GameManager& operator=(const GameManager&) = delete;
    GameManager(const GameManager&)            = delete;
    GameManager(GameManager&&)                 = delete;
};