#include "EndingScene.hpp"

#include <glm/gtx/string_cast.hpp>

// Utils
glm::vec2 AnimatedText::s_viewport_size = glm::vec2(800, 600);

AnimatedText::AnimatedText(const Data& start, const Data& end, float duration, Animator::Tweet::Type type) :
    _start(start), 
    _end(end),
    _current(start),
    _tweet(std::make_unique<Animator::Tweet>(duration, type))
{
    // ..
}

void AnimatedText::draw() {
    _current.pos    = _tweet->update(_start.pos,   _end.pos);
    _current.size   = _tweet->update(_start.size,  _end.size);
    _current.color  = _tweet->update(_start.color, _end.color);
    _current.text   = _tweet->update(_start.text,  _end.text);

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

void EndingScene::_createScenario() {
    m_texts.push_back(AnimatedText(
        { "Perspective", {0.45f, 0.80f}, 0.8f, glm::vec3(0.05f, 0.05f, 0.06f) },
        { "Perspective", {0.45f, 0.80f}, 0.8f, glm::vec3(1.0f, 1.0f, 1.0f) },
        2.0f, Animator::Tweet::Type::Quadratic
    ));
}

void EndingScene::draw() {
    // Draw texts
    for (auto& text : m_texts) {
        text.draw();
    }
    //TextEngine::Write("Special thanks to my wife,", 10.0f, m_height - 20.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
    //TextEngine::Write("without whom this game would have been completed 2 weeks ago.", 50.0f, m_height - 40.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));

    //TextEngine::Write("Perspective", m_width * 0.45f, m_height * 0.8f, 0.8f, glm::vec3(1.0f, 1.0f, 1.0f));
    //TextEngine::Write("What are the other things hidden from the view?", m_width * 0.375f, m_height * 0.8f - 40.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
}
