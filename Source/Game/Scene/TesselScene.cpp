#include "TesselScene.hpp"

#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>

#include <glm/gtc/matrix_transform.hpp>

// Scene instance
TesselScene::TesselScene() : 
    BaseScene(), 
    m_input(GL_STATIC_DRAW),
    m_output(GL_DYNAMIC_COPY) 
{
    // Camera
    m_projection = glm::perspective(glm::radians<float>(25.0f), 1400.0f / 800.0f, 0.1f, 100.0f);
    m_modelview  = glm::lookAt(glm::vec3(1.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // Physx
    m_physx
        .attachSource(GL_COMPUTE_SHADER, ShaderSource{}
            .add_cp_layout("in", { "1", "1", "1" })
            .add_struct("buffer InputMatrix", { "float matrix_input[9]" }, "0")
            .add_struct("buffer OutputMatrix", { "float matrix_output[9]" }, "1")
            .add_var("uniform", "float", "time")
            .add_func("void", "main", "", R"_main_(
                for(int i = 0; i < 9; i++) {
                    matrix_output[i] = matrix_input[i] * cos(time + i*20);
                }
            )_main_").str()
        )
        .link();

    // Input
    m_input.bindData(std::vector<float>{
        1.5f, 0.5f, 1.0f,
        0.2f, 1.0f, 1.5f,
        1.0f, 0.3f, 1.0f
    });
    m_output.bindData(9);

    // Create program shaders
    m_shaders["tessPoints"].attachSource(GL_GEOMETRY_SHADER,    
        #include "../../Resources/Waves/WaveGeomPoints.glsl"
    );
    m_shaders["tessLines"].attachSource(GL_GEOMETRY_SHADER, 
        #include "../../Resources/Waves/WaveGeomLines.glsl"
    );
    m_shaders["tessTriangles"].attachSource(GL_GEOMETRY_SHADER, 
        #include "../../Resources/Waves/WaveGeomTriangles.glsl"
    );

    // Commons shaders attached and params bound
    for (auto& itShader : m_shaders) {
        auto& shader = itShader.second;

        shader.attachSource(GL_VERTEX_SHADER,          
                #include "../../Resources/Waves/WaveVert.glsl"
            ).attachSource(GL_TESS_CONTROL_SHADER,    
                #include "../../Resources/Waves/WaveTControl.glsl"
            ).attachSource(GL_TESS_EVALUATION_SHADER, 
                #include "../../Resources/Waves/WaveTEval.glsl"
            ).attachSource(GL_FRAGMENT_SHADER,        
                #include "../../Resources/Waves/WaveFrag.glsl"
            ).link();

        shader.set("Projection", m_projection);
        shader.set("Modelview", m_modelview);

        shader.set("TessLevelInner", 2.0f);
        shader.set("TessLevelOuter", 2.0f);
        shader.set("time", 0.0f);
    }

    // Different params bound
    m_shaders["tessLines"]
        .set("Color", 0.0f, 1.0f, 0.0f)
        .set("zIndex", 0.02f);

    m_shaders["tessPoints"]
        .set("Color", 1.0f, 0.0f, 0.0f)
        .set("zIndex", 0.01f);

    m_shaders["tessTriangles"]
        .set("Color", 0.0f, 0.0f, 1.0f)
        .set("zIndex", 0.0f);
}

void TesselScene::resize(int width, int height) {
    // ..
}

void TesselScene::draw() {
    static float time = 0.0f;
    time += 1.0f / 60.0f;

    // Compute physics
    m_input.bind(0);
    m_output.bind(1);

    m_physx.use();
    m_physx.compute(1, 1, 1);
    m_physx.syncStorage();

    m_output.retrieve();
    m_output.bindUniform(0);

    // Render
    for (auto& itShader : m_shaders) {
        auto& shader = itShader.second;
        auto& name = itShader.first;

        if (name != "tessTriangles")
            continue;

        shader.set("time", time);
        shader.setBlock("Normals", 0);

        shader.use();
        m_shapeGround.bind();
        m_shapeGround.draw();
    }

    // Draw texts
    TextEngine::Write("Tesselation baby", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
