#include "SimpleScene.hpp"

#include <glm/glm.hpp>

SimpleScene::SimpleScene() : BaseScene(),
    m_circle(0.5f),
    m_square(0.5f),
    m_points({
        { -0.5f,  0.5f, 1.0f, 0.0f, 0.0f}, // top-left
        { 0.5f,   0.5f, 0.0f, 1.0f, 0.0f}, // top-right
        { 0.5f,  -0.5f, 0.0f, 0.0f, 1.0f}, // bottom-right
        { -0.5f, -0.5f, 1.0f, 1.0f, 0.0f}  // bottom-left
    }) 
{
    // Basic shaders for the shapes
    m_simpleShader.attachSource(GL_VERTEX_SHADER, 
#include "../../Shaders/Base/base.vs"
    );
    m_simpleShader.attachSource(GL_GEOMETRY_SHADER, 
#include "../../Shaders/Base/base.gs"
    );
    m_simpleShader.attachSource(GL_FRAGMENT_SHADER, 
#include "../../Shaders/Base/base.fs"
    );

    m_simpleShader.link();
}

void SimpleScene::draw() {
    // Background
    glClearColor(0.05f, 0.05f, 0.06f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Some texts
    TextEngine::Write("Some text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
    TextEngine::Write("Yo world!", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

    // Some shapes
    m_simpleShader.use();

    // Draw a circle
    m_circle.bind();
    m_circle.draw();

    // Draw a square
    m_square.bind();
    m_square.draw();

    // Draw points
    m_points.bind();
    m_points.draw();
}