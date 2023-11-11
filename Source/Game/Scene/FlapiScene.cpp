#include "FlapiScene.hpp"

#include <algorithm>
#include <random>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

// Scene instance
FlapiScene::FlapiScene() : 
    BaseScene(), 
    m_input(GL_STATIC_DRAW),
    m_output(GL_DYNAMIC_COPY),
    m_time(0.0f)
{
    // Magic size of something
    const int N = 15*15;

    // Physx
    m_physx
        .attachSource(GL_COMPUTE_SHADER, ShaderSource{}
            .add_cp_layout("in", { "1", "1", "1" })
            .add_struct("buffer InputMatrix",  { "float matrix_input["  + std::to_string(N) + "]"},  "0")
            .add_struct("buffer OutputMatrix", { "float matrix_output[" + std::to_string(N) + "]" }, "1")
            .add_var("uniform", "float", "time")
            .add_func("void", "main", "", "                                    \
                for(int i = 0; i < " + std::to_string(N) + "; i++) {"          \
                    "matrix_output[i] = matrix_input[i] * cos(time + i * 20);" \
                "}").str()
        )
        .link();

    // Input
    std::random_device rnd_device;
    std::knuth_b e2(rnd_device());
    std::uniform_real_distribution<float> dist{ -2.0f, 2.0f};
    std::vector<float> inputDistrib(N);

    std::generate(inputDistrib.begin(), inputDistrib.end(), [&dist, &e2]() { return dist(e2); });

    m_input.bindData(inputDistrib);
    m_output.bindData(N);

    // Create program shaders
    m_shaders["tessPoints"].attachSource(GL_GEOMETRY_SHADER,    
        #include "Waves/WaveGeomPoints.glsl"
    );
    m_shaders["tessLines"].attachSource(GL_GEOMETRY_SHADER, 
        #include "Waves/WaveGeomLines.glsl"
    );
    m_shaders["tessTriangles"].attachSource(GL_GEOMETRY_SHADER, 
        #include "Waves/WaveGeomTriangles.glsl"
    );

    // Commons shaders attached and params bound
    for (auto& itShader : m_shaders) {
        auto& shader = itShader.second;

        shader.attachSource(GL_VERTEX_SHADER,          
                #include "Waves/WaveVert.glsl"
            ).attachSource(GL_TESS_CONTROL_SHADER,    
                #include "Waves/WaveTControl.glsl"
            ).attachSource(GL_TESS_EVALUATION_SHADER, 
                R"_(
                    #version 460

                    /* Possible:
                        triangles,
                        quads
                    */
                    layout(quads, equal_spacing, ccw) in;

                    in vec3 tcCoord[];
                    out float rho;

                    uniform mat4 Projection;
                    uniform mat4 Modelview;
                    uniform float time;

                    uniform Normals {
                        float matrix[)_" + std::to_string(N) + R"_(];
                    } Output;

                    void main() {
                        // With quads
                        float u = gl_TessCoord.x;
                        vec3 p0 = mix(tcCoord[0], tcCoord[3], u);
                        vec3 p1 = mix(tcCoord[1], tcCoord[2], u);

                        float v = gl_TessCoord.y;
                        vec3 p  = mix(p0, p1, v);
    
                        // Heights
                        int N = int(sqrt()_" + std::to_string(N) + R"_());
                        float rx = (N-1) * (p.x + 1.0) * 0.5; rx = clamp(0, N-1, rx); // 0 - N-1
                        float ry = (N-1) * (p.y + 1.0) * 0.5; ry = clamp(0, N-1, ry); // 0 - N-1

                        int i0 = int(round(rx));
                        int j0 = int(round(ry));
                        float dr = 1.0 - sqrt(pow(i0-rx, 2) + pow(j0-ry, 2));

                        float oz = 0.20 * Output.matrix[i0 + N*j0] * dr;
                        rho = 0.5*(1.0 + oz / 0.15);
                        time;

                        gl_Position = Projection * Modelview * vec4(p.xy, p.z + oz, 1.0);
                    }
                    )_"
            ).attachSource(GL_FRAGMENT_SHADER,        
                #include "Waves/WaveFrag.glsl"
            ).link();

        shader
            .set("TessLevelInner", 2.0f)
            .set("TessLevelOuter", 2.0f)
            .set("time", 0.0f);
    }

    // Different params bound
    m_shaders["tessLines"]
        .set("Color", glm::vec3(0.0f, 1.0f, 0.0f))
        .set("zIndex", 0.02f);

    m_shaders["tessPoints"]
        .set("Color", glm::vec3(1.0f, 0.0f, 0.0f))
        .set("zIndex", 0.01f);

    m_shaders["tessTriangles"]
        .set("Color", glm::vec3(0.0f, 0.0f, 1.0f))
        .set("zIndex", 0.0f);
}

void FlapiScene::resize(int width, int height) {
    // Update scene internal
    BaseScene::resize(width, height);

    // Camera
    m_camera.projection = glm::perspective(glm::radians<float>(25.0f), (float)width / height, 0.1f, 100.0f);
    m_camera.modelview = glm::lookAt(glm::vec3(1.0f, 3.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void FlapiScene::draw() {
    m_time += 1e-1f;

    // Compute physics
    m_input.bind(0);
    m_output.bind(1);

    m_physx.use();
    m_physx.set("time", m_time);
    m_physx.compute(1, 1, 1);
    m_physx.syncStorage();

    m_output.retrieve();
    m_output.bindUniform(0);

    // Render
    for (auto& itShader : m_shaders) {
        auto& shader = itShader.second;
        auto& name = itShader.first;

        shader.set("time", m_time);
        shader.set("TessLevelInner", 2.0f + m_time / 10);
        shader.set("TessLevelOuter", 2.0f + m_time / 10);
        shader.set("Projection", m_camera.projection);
        shader.set("Modelview", m_camera.modelview);
        shader.setBlock("Normals", 0);

        shader.use();
        m_shapeGround.bind();
        m_shapeGround.draw();
    }

    // Draw texts
    TextEngine::Write("Flapi scene", 10.0f, 10.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
}
