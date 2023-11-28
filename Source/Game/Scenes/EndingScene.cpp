#include "EndingScene.hpp"

#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

// Scene instance
EndingScene::EndingScene() :
    BaseScene(),
    m_sand(glm::vec3(0.01f, 0.01f, 0.01f)),
    m_ground(glm::vec3(0.5f, 0.5f, 0.05f)),
    m_slime(0.1f)
{
    // Camera
    m_camera.position    = glm::vec3(-1.0f, 3.8f, 0.0f);
    m_camera.direction   = glm::vec3(-1.0f, 0.0f, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // Scenario
    _createScenario();

    // Objects
    std::default_random_engine gen;
    std::uniform_real_distribution<float> dstr(-1.0f, +1.0f);

    m_sand.models.resize(2000);
    std::generate(m_sand.models.begin(), m_sand.models.end(), [&]() -> glm::mat4 {
        return glm::translate(glm::mat4(1.0f), glm::vec3(0.30f * dstr(gen), 0.0f, 1.5f + dstr(gen)));
    });
    m_sand.create();
}

void EndingScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);
    AnimatedText::s_viewport_size = glm::vec2(width, height);

    // Camera
    _update_camera();
}

void EndingScene::draw() {
    _update_camera();

    // Draw texts
    for (auto& drawable : m_timeline.get()) {
        drawable->draw();
    }

    // Draw objects
    m_ground.draw(m_camera, {}, {}, m_lights);
    m_slime.draw(m_camera, {}, {}, m_lights);
    m_sand.draw(m_camera, m_lights);
}


// --- Private ---
void EndingScene::_update_camera() {
    float aspect = (float)m_width / m_height;

    m_camera.lookAt(glm::vec3(0, 0, 1));
    m_camera.usePerspective(aspect);
}

void EndingScene::_createScenario() {
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

    // Credit to an awesome man, whose genious has yet to be recognized
    const std::string resource_name = "Remy Chauvin"; // i shit on people calling their employees 'resources'.
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
        "Lead Dream Supplier",
        "Employee of the Month",    // TODO: ask the HR lead director if this shall be renamed 'resource of the month'.
    };

    for (size_t i = 0; i < resource_job.size(); i++) 
    {
        if (resource_job[i].empty())
            continue;

        m_timeline
            .put(SlideTop(ATextD{ resource_job[i], {0.60f, -0.05f * i}, 0.7f, text_color }, 9.0f, 21.0f), 9.0f, 30.0f)
            .put(SlideTop(ATextD{ resource_name,   {0.85f, -0.05f * i}, 0.5f, text_color }, 9.0f, 21.0f), 9.0f, 30.0f)
        ;
    }
}

