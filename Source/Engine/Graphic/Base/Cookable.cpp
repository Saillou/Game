#include "Cookable.hpp"

#include <glad/glad.h>

// - Recipes
Cookable* Cookable::addRecipe(const CookType& type, const glm::vec4& color) {
    m_shaders.push_back(std::make_unique<Shader>());
    UShader& recipe = m_shaders.back();

    switch (type) {
    case CookType::Solid:
        _set_shader_single(recipe);
        break;

    case CookType::Border:
        _set_shader_single(recipe);
        _set_shader_border(recipe);
        break;

    case CookType::Point:
        _set_shader_single(recipe);
        _set_shader_point(recipe);
        break;

    case CookType::Batch:
        _set_shader_batch(recipe);
        break;

    default:
        return this;
    }

    _set_shader_light(recipe);

    recipe->link();

    // Set uniforms
    recipe->use()
        .set("color", color);

    // Allow chained calls
    return this;
}

// - Shaders
// Vertex
void Cookable::_set_shader_batch(UShader& shader) {
    shader->
        attachSource(GL_VERTEX_SHADER, ShaderSource{}
            .add_var("layout (location = 0) in", "vec3", "aPos")
            .add_var("layout (location = 1) in", "vec3", "aNormal")
            .add_var("layout (location = 2) in", "mat4", "Model")

            .add_var("uniform", "mat4", "Projection")
            .add_var("uniform", "mat4", "View")

            .add_var("out", "vec3", "Normal")
            .add_var("out", "vec3", "FragPos")

            .add_func("void", "main", "", R"_main_(
                FragPos = vec3(Model * vec4(aPos, 1.0));
                Normal = mat3(transpose(inverse(Model))) * aNormal;  
    
                gl_Position = Projection * View * vec4(FragPos, 1.0);
            )_main_").str()
        );
}

void Cookable::_set_shader_single(UShader& shader) {
    shader->
        attachSource(GL_VERTEX_SHADER, ShaderSource{}
            .add_var("in", "vec3", "aPos")
            .add_var("in", "vec3", "aNormal")

            .add_var("uniform", "mat4", "Projection")
            .add_var("uniform", "mat4", "View")
            .add_var("uniform", "mat4", "Model")

            .add_var("out", "vec3", "Normal")
            .add_var("out", "vec3", "FragPos")

            .add_func("void", "main", "", R"_main_(
                FragPos = vec3(Model * vec4(aPos, 1.0));
                Normal = mat3(transpose(inverse(Model))) * aNormal;  
    
                gl_Position = Projection * View * vec4(FragPos, 1.0);
            )_main_").str()
        );
}

// Geometry
void Cookable::_set_shader_border(UShader& shader) {
    shader->
        attachSource(GL_GEOMETRY_SHADER, ShaderSource{}
            .add_var("in", "layout", "(triangles)")
            .add_var("out", "layout", "(line_strip, max_vertices = 4)")
            .add_func("void", "main", "", R"_main_(
                    gl_Position     = gl_in[1].gl_Position; EmitVertex();
                    gl_Position     = gl_in[2].gl_Position; EmitVertex(); 
                    EndPrimitive();

                    gl_Position     = gl_in[0].gl_Position; EmitVertex();
                    gl_Position     = gl_in[1].gl_Position; EmitVertex(); 
                    EndPrimitive();
                )_main_").str()
        );
}

void Cookable::_set_shader_point(UShader& shader) {
    shader->
        attachSource(GL_GEOMETRY_SHADER, ShaderSource{}
            .add_var("in", "layout", "(triangles)")
            .add_var("out", "layout", "(points, max_vertices = 2)")
            .add_func("void", "main", "", R"_main_(
                    gl_Position     = gl_in[0].gl_Position; EmitVertex();
                    EndPrimitive();

                    gl_Position     = gl_in[1].gl_Position; EmitVertex(); 
                    EndPrimitive();
                )_main_").str()
        );
}

// Fragments
void Cookable::_set_shader_light(UShader& shader) {
    shader->
        attachSource(GL_FRAGMENT_SHADER, ShaderSource{}
            .add_var("in", "vec3", "Normal")
            .add_var("in", "vec3", "FragPos")

            .add_var("uniform", "vec4", "color")
            .add_var("uniform", "vec3", "CameraPos")
            .add_var("uniform", "lowp int", "LightLength")
            .add_var("uniform", "vec3", "LightPos")
            .add_var("uniform", "vec4", "LightColor")

            .add_var("out", "vec4", "FragColor")

            .add_func("void", "main", "", R"_main_(
                // Shall use light ?
                if(LightColor == vec4(0, 0, 0, 0)) {
                    FragColor = color;
                    return;
                }

                // ambient
                float ambientStrength = 0.1;
                vec3 ambient = ambientStrength * vec3(LightColor.rgb);

                // diffuse 
                vec3 normDir = normalize(Normal);
                vec3 lightDir = normalize(LightPos - FragPos);
                float diff = max(dot(normDir, lightDir), 0.0);
                vec3 diffuse = diff * vec3(LightColor.rgb);

                // specular
                float specularStrength = 0.5;
                vec3 cameraDir = normalize(CameraPos - FragPos);
                vec3 reflectDir = reflect(-lightDir, normDir);  
                float spec = pow(max(dot(cameraDir, reflectDir), 0.0), 32);
                vec3 specular = specularStrength * spec * vec3(LightColor.rgb);

                vec3 result = (ambient + diffuse + specular) * color.rgb;
                FragColor = vec4(result, color.a);
            )_main_").str()
        );
}
