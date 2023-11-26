#include "IntroScene.hpp"

#include <algorithm>
#include <ctime>
#include <random>

#include <glm/gtx/string_cast.hpp>

// -- Objects --
SphereBatch::SphereBatch(float radius) :
    object(std::make_unique<Sphere>(radius))
{
    object->addRecipe(Cookable::CookType::Batch, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void SphereBatch::create() {
    object->shape()->createBatch(models);
}

void SphereBatch::update() {
    object->shape()->updateBatch(models);
}

void SphereBatch::draw(const Camera& camera, const std::vector<std::unique_ptr<Light>>& lights) {
    object->drawBatch((int)models.size(), camera, lights);
}

// -- Scene instance --
IntroScene::IntroScene() :
    BaseScene(),
    m_title(0.0125f),
    m_decors(0.25f),
    m_next(1.0f)
{
    // Camera
    m_camera.position    = glm::vec3(0.0f, 2.0f, 0.0f);
    m_camera.direction   = glm::vec3(0.0f, 0.0, 0.0f);
    m_camera.fieldOfView = 45.0f;

    // - Generate batches
    // Random engine
    std::default_random_engine gen;
    std::uniform_real_distribution<float> dstr(-50.0f, +50.0f);

    // Draw decors
    m_decors.models.resize(2000);
    std::generate(m_decors.models.begin(), m_decors.models.end(), [&]() -> glm::mat4 {
        return 
            glm::scale(
                glm::translate(
                    glm::mat4(1.0f), 
                    glm::vec3(dstr(gen), dstr(gen), dstr(gen))
                ),
                0.05f * std::abs(dstr(gen)) * glm::vec3(1.0f, 1.0f, 1.0f)
            );
    });

    // Draw title
    m_title.models.resize(_get_title_pos().size());
    std::generate(m_title.models.begin(), m_title.models.end(), [&]() -> glm::mat4 {
        return glm::translate(
            glm::mat4(1.0f),
            glm::vec3(dstr(gen), dstr(gen), dstr(gen))
        );
    });

    // Draw target
    m_next.models.resize(1);
    m_next.models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 0.0, 50.0f));

    // Create batch
    m_title.create();
    m_decors.create();
    m_next.create();
}

void IntroScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    _update_camera();
}

void IntroScene::draw() {
    // Camera
    _update_camera();

    // Update
    for (size_t i = 0; i < m_title.models.size(); i++) 
    {
        const auto _get_pos = _get_title_pos(i);
        
        const glm::vec2& pos = _get_pos[0];
        glm::vec4& model_pos = m_title.models[i][3];

        model_pos[0] = model_pos[0] * 0.99f + (0.5f - pos.x) * 0.01f;
        model_pos[1] = model_pos[1] * 0.98f;
        model_pos[2] = model_pos[2] * 0.99f + (0.5f - pos.y) * 0.01f;
    }
    m_title.update();

    // Draw universe
    m_title.draw(m_camera, m_lights);
    m_decors.draw(m_camera, m_lights);
    m_next.draw(m_camera, m_lights);
}

void IntroScene::_update_camera() {
    float aspect = (float)m_width / m_height;

    m_camera.lookAt(glm::vec3(0, 0, 1));
    m_camera.usePerspective(aspect);
}


// ---
const std::vector<glm::vec2> IntroScene::_get_title_pos(size_t i) const {
    /* ~~~~ Memo ~~~~~~
        To change that: 
          - Draw the text you want, black on white
          - use opencv
          - thresh on value 0
          - normalize coordinate
    ~~~~~~~~~~~~~~~~~~~~ */

    static const std::vector<glm::vec2> pos = 
    {
        {0,0.346939},
        {0.0204082,0.346939},
        {0.0408163,0.346939},
        {0.0612245,0.346939},
        {0,0.367347},
        {0.0204082,0.367347},
        {0.0408163,0.367347},
        {0.0816327,0.367347},
        {0.755102,0.367347},
        {0,0.387755},
        {0.0204082,0.387755},
        {0.0612245,0.387755},
        {0.0816327,0.387755},
        {0,0.408163},
        {0.0204082,0.408163},
        {0.0612245,0.408163},
        {0.0816327,0.408163},
        {0.673469,0.408163},
        {0,0.428571},
        {0.0204082,0.428571},
        {0.0612245,0.428571},
        {0.0816327,0.428571},
        {0.122449,0.428571},
        {0.142857,0.428571},
        {0.163265,0.428571},
        {0.204082,0.428571},
        {0.22449,0.428571},
        {0.244898,0.428571},
        {0.285714,0.428571},
        {0.306122,0.428571},
        {0.326531,0.428571},
        {0.387755,0.428571},
        {0.408163,0.428571},
        {0.428571,0.428571},
        {0.489796,0.428571},
        {0.510204,0.428571},
        {0.530612,0.428571},
        {0.591837,0.428571},
        {0.612245,0.428571},
        {0.632653,0.428571},
        {0.673469,0.428571},
        {0.693878,0.428571},
        {0.714286,0.428571},
        {0.755102,0.428571},
        {0.938776,0.428571},
        {0.959184,0.428571},
        {0.979592,0.428571},
        {0,0.44898},
        {0.0204082,0.44898},
        {0.0408163,0.44898},
        {0.0612245,0.44898},
        {0.0816327,0.44898},
        {0.122449,0.44898},
        {0.163265,0.44898},
        {0.204082,0.44898},
        {0.285714,0.44898},
        {0.387755,0.44898},
        {0.428571,0.44898},
        {0.489796,0.44898},
        {0.530612,0.44898},
        {0.591837,0.44898},
        {0.632653,0.44898},
        {0.673469,0.44898},
        {0.755102,0.44898},
        {0.877551,0.44898},
        {0.897959,0.44898},
        {0.938776,0.44898},
        {0.979592,0.44898},
        {0,0.469388},
        {0.0204082,0.469388},
        {0.0408163,0.469388},
        {0.0612245,0.469388},
        {0.122449,0.469388},
        {0.142857,0.469388},
        {0.163265,0.469388},
        {0.204082,0.469388},
        {0.285714,0.469388},
        {0.306122,0.469388},
        {0.387755,0.469388},
        {0.428571,0.469388},
        {0.489796,0.469388},
        {0.510204,0.469388},
        {0.530612,0.469388},
        {0.591837,0.469388},
        {0.673469,0.469388},
        {0.755102,0.469388},
        {0.816327,0.469388},
        {0.877551,0.469388},
        {0.938776,0.469388},
        {0.959184,0.469388},
        {0.979592,0.469388},
        {0,0.489796},
        {0.0204082,0.489796},
        {0.122449,0.489796},
        {0.204082,0.489796},
        {0.306122,0.489796},
        {0.326531,0.489796},
        {0.387755,0.489796},
        {0.428571,0.489796},
        {0.489796,0.489796},
        {0.591837,0.489796},
        {0.673469,0.489796},
        {0.755102,0.489796},
        {0.816327,0.489796},
        {0.836735,0.489796},
        {0.857143,0.489796},
        {0.877551,0.489796},
        {0.938776,0.489796},
        {0,0.510204},
        {0.0204082,0.510204},
        {0.122449,0.510204},
        {0.204082,0.510204},
        {0.326531,0.510204},
        {0.387755,0.510204},
        {0.428571,0.510204},
        {0.489796,0.510204},
        {0.591837,0.510204},
        {0.673469,0.510204},
        {0.755102,0.510204},
        {0.836735,0.510204},
        {0.857143,0.510204},
        {0.938776,0.510204},
        {0,0.530612},
        {0.0204082,0.530612},
        {0.122449,0.530612},
        {0.142857,0.530612},
        {0.163265,0.530612},
        {0.204082,0.530612},
        {0.285714,0.530612},
        {0.306122,0.530612},
        {0.326531,0.530612},
        {0.387755,0.530612},
        {0.408163,0.530612},
        {0.428571,0.530612},
        {0.489796,0.530612},
        {0.510204,0.530612},
        {0.530612,0.530612},
        {0.591837,0.530612},
        {0.612245,0.530612},
        {0.632653,0.530612},
        {0.673469,0.530612},
        {0.693878,0.530612},
        {0.755102,0.530612},
        {0.836735,0.530612},
        {0.938776,0.530612},
        {0.959184,0.530612},
        {0.979592,0.530612},
        {0,0.55102},
        {0.0204082,0.55102},
        {0.0408163,0.55102},
        {0.387755,0.55102},
        {0.387755,0.571429},
        {0.387755,0.591837},
        {0.367347,0.612245},
        {0.387755,0.612245},
        {0.408163,0.612245}
    };

    if(i >= 0 && i < pos.size())
        return { pos[i] };

    return pos;
}