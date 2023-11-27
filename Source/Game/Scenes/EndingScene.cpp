#include "EndingScene.hpp"

#include <glm/gtx/string_cast.hpp>

using ATextD = AnimatedText::Data;
using uAText = std::shared_ptr<AnimatedText>;

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

// Helper functions
static uAText FadeIn(const ATextD& state, float start_time, float duration) {
    const auto background_color = glm::vec3(0.05f, 0.05f, 0.06f);

    return std::make_shared<AnimatedText>
    (
        ATextD{ state.text, state.pos, state.size, background_color },
        state,
        start_time, duration,
        Animator::Tweet::Type::Quadratic
    );
};

static uAText FadeOut(const ATextD& state, float start_time, float duration) {
    const auto background_color = glm::vec3(0.05f, 0.05f, 0.06f);

    return std::make_shared<AnimatedText>
    (
        state,
        ATextD{ state.text, state.pos, state.size, background_color },
        start_time, duration,
        Animator::Tweet::Type::Quadratic
    );
};

static uAText SlideTop(const ATextD& state, float start_time, float duration) {
    return std::make_shared<AnimatedText>
    (
        state,
        ATextD{ state.text, glm::vec2(state.pos.x, state.pos.y + 2.0f), state.size, state.color },
        start_time, duration,
        Animator::Tweet::Type::Linear
    );
};

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
    const auto text_color = glm::vec3(1.0f, 1.0f, 1.0f);

    // Title | subtitle
    const std::string title = "Perspective";
    const std::string subtitle = "The Falling";

    m_timeline
        .put(FadeIn(ATextD  { title, {0.45f, 0.80f}, 0.8f, text_color }, 0.0f, 1.5f), 0.0f, 4.0f)
        .put(FadeOut(ATextD { title, {0.45f, 0.80f}, 0.8f, text_color }, 4.0f, 0.5f), 4.0f, 4.5f)
        .put(FadeIn(ATextD  { subtitle, { 0.50f, 0.75f }, 0.6f, text_color }, 1.5f, 2.0f), 1.5f, 4.0f)
        .put(FadeOut(ATextD { subtitle, { 0.50f, 0.75f }, 0.6f, text_color }, 4.0f, 1.0f), 4.0f, 5.0f)
    ;

    // Special 'thanks'
    const std::string thanks_name = "Special thanks to my wife,";
    const std::string thanks_reason = "without whom this game would have been completed 2 weeks ago.";

    m_timeline
        .put(FadeIn(ATextD  { thanks_name, {0.55f, 0.80f}, 0.8f, text_color }, 5.0f, 1.5f), 5.0f, 7.0f)
        .put(FadeOut(ATextD { thanks_name, {0.55f, 0.80f}, 0.8f, text_color }, 7.0f, 0.5f), 7.0f, 9.0f)
        .put(FadeIn(ATextD  { thanks_reason, {0.40f, 0.75f}, 0.6f, text_color }, 6.0f, 1.5f), 6.0f, 8.0f)
        .put(FadeOut(ATextD { thanks_reason, {0.40f, 0.75f}, 0.6f, text_color }, 8.0f, 1.5f), 8.0f, 9.5f)
    ;

    // Credit to an awesome man, who's genious is unrecognized
    float debug_off = 9.0f;
    const std::string resource_name = "Remy Chauvin"; // if not obvious enough, it's a variable name troll: i shit on people calling their employees 'resources'.
    const std::vector<std::string> resource_job = 
    {
        "Lead Producer",
        "Creative Director",
        "Artistic Director",
        "Game Design Director",
        "Lead Programmer",
        "",
        "Technical Director",
        "Lead Level Design",
        "Photography Director",
        "Character Director",
        "Animation Director",
        "",
        "Coffee Maker",
        "Music Compositor",
        "Executive Joke Producer",
        "Employee of the Month",
    };

    for (size_t i = 0; i < resource_job.size(); i++) 
    {
        if (resource_job[i].empty())
            continue;

        m_timeline
            .put(SlideTop(ATextD{ resource_job[i], {0.60f, -0.05f * i}, 0.7f, text_color }, 9.0f, 11.0f), 9.0f, 20.0f)
            .put(SlideTop(ATextD{ resource_name,   {0.85f, -0.05f * i}, 0.5f, text_color }, 9.0f, 11.0f), 9.0f, 20.0f)
        ;
    }
}

void EndingScene::draw() {
    // Draw texts
    for (auto& drawable : m_timeline.get()) {
        drawable->draw();
    }
}
