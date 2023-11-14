#include "Cookable.hpp"

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
