#include "EndingScene.hpp"

#include <glm/gtx/string_cast.hpp>

// Utils
glm::vec2 AnimatedText::s_viewport_size = glm::vec2(800, 600);

AnimatedText::AnimatedText(const Data& start, const Data& end, float start_offset, float duration, Animator::Tweet::Type type) :
    _start(start), 
    _end(end),
    _current(start),
    _tweet(start_offset, duration, type)
{
    // ..
}

void AnimatedText::draw() {
    _current.pos    = _tweet.update(_start.pos,   _end.pos);
    _current.size   = _tweet.update(_start.size,  _end.size);
    _current.color  = _tweet.update(_start.color, _end.color);
    _current.text   = _tweet.update(_start.text,  _end.text);

    TextEngine::Write(
        _current.text,
        s_viewport_size.x * _current.pos.x, s_viewport_size.y * _current.pos.y,
        _current.size,
        _current.color
    );
}

// Scene instance
EndingScene::EndingScene() :
    BaseScene()
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 3.8f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0f, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // Scenario
    _createScenario();
}

void EndingScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);
    AnimatedText::s_viewport_size = glm::vec2(width, height);
}

void EndingScene::_createScenario() 
{
    // Common stuff
    using ADText = AnimatedText::Data;

    const auto text_color       = glm::vec3(1.0f, 1.0f, 1.0f);
    const auto background_color = glm::vec3(0.05f, 0.05f, 0.06f);

    // Helper functions
    auto _fonduIn = [=](const ADText& state, float start_time, float duration) {
        return std::make_shared<AnimatedText>
            (
                ADText{ state.text, state.pos, state.size, background_color },
                state,
                start_time, duration,
                Animator::Tweet::Type::Quadratic
            );
    };

    auto _fonduOut = [=](const ADText& state, float start_time, float duration) {
        return std::make_shared<AnimatedText>
            (
                state,
                ADText{ state.text, state.pos, state.size, background_color },
                start_time, duration,
                Animator::Tweet::Type::Quadratic
            );
    };

    // Title | subtitle
    const std::string title = "Perspective";
    const std::string subtitle = "The Falling";

    m_timeline
        .put(_fonduIn(ADText    { title, {0.45f, 0.80f}, 0.8f, text_color }, 0.0f, 1.5f), 0.0f, 4.0f)
        .put(_fonduOut(ADText   { title, {0.45f, 0.80f}, 0.8f, text_color }, 4.0f, 0.5f), 4.0f, 4.5f)
        .put(_fonduIn(ADText    { subtitle, { 0.50f, 0.75f }, 0.6f, text_color }, 1.5f, 2.0f), 1.5f, 4.0f)
        .put(_fonduOut(ADText   { subtitle, { 0.50f, 0.75f }, 0.6f, text_color }, 4.0f, 1.0f), 4.0f, 5.0f)
    ;

    // Special 'thanks'
    const std::string thanks_name = "Special thanks to my wife,";
    const std::string thanks_reason = "without whom this game would have been completed 2 weeks ago.";

    m_timeline
        .put(_fonduIn(ADText    { thanks_name, {0.55f, 0.80f}, 0.8f, text_color }, 5.0f, 1.5f), 5.0f, 7.0f)
        .put(_fonduOut(ADText   { thanks_name, {0.55f, 0.80f}, 0.8f, text_color }, 7.0f, 0.5f), 7.0f, 9.0f)
        .put(_fonduIn(ADText    { thanks_reason, {0.40f, 0.75f}, 0.6f, text_color }, 6.0f, 1.5f), 6.0f, 8.0f)
        .put(_fonduOut(ADText   { thanks_reason, {0.40f, 0.75f}, 0.6f, text_color }, 8.0f, 1.5f), 8.0f, 9.5f)
    ;

    // Credit to an awesome man, who's genious is unrecognized

}

void EndingScene::draw() {
    // Draw texts
    for (auto& drawable : m_timeline.get()) {
        drawable->draw();
    }
}
