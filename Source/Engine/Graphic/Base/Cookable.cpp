#include "Cookable.hpp"

#include <glad/glad.h>

// - Recipes
Cookable* Cookable::addRecipe(const CookType& type, const glm::vec4& color) {
    m_shaders.push_back(std::make_unique<Shader>());
    UShader& recipe = m_shaders.back();

    switch (type) {
    case CookType::Solid:
        _set_shader_solid(recipe);
        break;

    case CookType::Border:
        _set_shader_border(recipe);
        break;

    case CookType::Point:
        _set_shader_point(recipe);
        break;

    default:
        return this;
    }

    // Set uniforms
    recipe->use().set("color", color);

    // Allow chained calls
    return this;
}

// - Shader
void Cookable::_set_shader_common(UShader& shader) {
    shader->
        attachSource(GL_VERTEX_SHADER, ShaderSource{}
            .add_var("in", "vec3", "aPos")
            .add_var("uniform", "mat4", "Projection")
            .add_var("uniform", "mat4", "View")
            .add_var("uniform", "mat4", "Model")
            .add_func("void", "main", "", R"_main_(
                gl_Position = Projection * View * Model * vec4(aPos, 1.0);
            )_main_").str()
        ).
        attachSource(GL_FRAGMENT_SHADER, ShaderSource{}
            .add_var("uniform", "vec4", "color")
            .add_var("out", "vec4", "FragColor")
            .add_func("void", "main", "", R"_main_(
                FragColor = color;
            )_main_").str()
        );
}

void Cookable::_set_shader_solid(UShader& shader) {
    _set_shader_common(shader);
    shader->link();
}
