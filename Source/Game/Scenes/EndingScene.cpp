#include "EndingScene.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

struct EndGround : public BaseItem {
    EndGround(const glm::vec3& dims) {
        _body = std::make_shared<BoxBody>(dims);
    };
};

struct EndSlime : public BaseItem {
    EndSlime(const float radius) {
        _body = std::make_shared<SphereBody>(radius);
    }
};


// Scene instance
EndingScene::EndingScene() :
    BaseScene(),
    m_sand(glm::vec3(0.01f, 0.01f, 0.01f)),
    m_ground(std::make_shared<EndGround>(glm::vec3(0.5f, 0.5f, 0.05f))),
    m_slime(std::make_shared<EndSlime>(0.05f)),
    m_light(std::make_shared<SphereBody>(0.01f))
{
    // Camera
    m_camera.position    = glm::vec3(-1.0f, 3.8f, +0.7f);
    m_camera.direction   = glm::vec3(-1.0f, 0.0f, +0.7f);
    m_camera.fieldOfView = 45.0f;

    // Scenario
    _createScenario();

    // Objects
    std::default_random_engine gen;
    std::uniform_real_distribution<float> dstr(-1.0f, +1.0f);

    m_sand.models.resize(1000);
    std::generate(m_sand.models.begin(), m_sand.models.end(), [&]() -> glm::mat4 {
        return glm::translate(glm::mat4(1.0f), glm::vec3(0.30f * dstr(gen), 0.0f, 3.5f + dstr(gen)));
    });
    m_sand.create();

    // Lightnings
    m_lights.push_back(std::make_unique<Light>(
        glm::vec3(0.0f, 0.0f, 1.5f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
    ));

    m_ground->body()->position = glm::vec3(0.0f, 0.0f, -0.1f);
}

void EndingScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);
    AnimatedText::s_viewport_size = glm::vec2(width, height);

    // Camera
    _update_camera();
}

void EndingScene::createActors() {
    // Physics
    m_slime->addAs(Physx::BodyType::Kinematic);
    m_ground->addAs(Physx::BodyType::Static);
}

void EndingScene::addSand() {
    if (m_sand_bodies.size() >= m_sand.models.size())
        return;

    auto boxBody = std::make_shared<BoxBody>(glm::vec3(0.01f, 0.01f, 0.01f));
    boxBody->position = m_sand.models[m_sand_bodies.size()][3];
    
    m_sand_bodies.push_back(
        Physx::Add(boxBody, Physx::BodyType::Dynamic)
    );
}

void EndingScene::draw() {
    float time = m_timeline.get_curr_time();

    // Conserve aspect ratio
    _update_camera();

    // Draw texts
    for (auto& drawable : m_timeline.get()) {
        drawable->draw();
    }

    // Move camera
    m_camera.position = glm::vec3(-1.0f + 0.1f * sin(time), 3.8f, +0.7f + 0.1f * cos(time));

    // Move light
    m_light->position     = glm::vec3(-1.0f + cos(time)*1.5f, sin(time) * sin(time), 1.0f + sin(time)*1.0f);
    m_lights[0]->position = m_light->position;

    // Move objects
    for (size_t i = 0; i < m_sand_bodies.size(); i++) {
        m_sand_bodies[i]->getTransform().getOpenGLMatrix(glm::value_ptr(m_sand.models[i]));
    }
    m_sand.update();

    // Draw objects
    if (time < 9.0f)
        m_light->draw(m_camera, {});

    if (time > 6.0f)
        m_ground->body()->draw(m_camera, m_lights);

    if (time > 9.0f)
        m_slime->body()->draw(m_camera, m_lights);

    if (time > 10.0f) {
        m_sand.draw(m_camera, m_lights);

        // Bit of sand
        static int i = 0;
        i = (i + 1) % 3;
        if(i == 0)
            addSand();
    }
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

