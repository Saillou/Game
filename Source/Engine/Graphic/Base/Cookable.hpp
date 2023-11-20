#pragma once

#include <glm/glm.hpp>

#include "../Shaders/Shader.hpp"
#include "../../../Utils/Caster.hpp"

// Objects
struct Cookable : public Object {
    // Basic possibilities
    enum class CookType {
        Solid, Border, Point
    };

    // Instance
    virtual ~Cookable() = default;

    virtual Cookable* addRecipe(const CookType& type, const glm::vec4& color);

protected:
    void _set_shader_common(UShader& shader);

    virtual void _set_shader_solid(UShader&);
    virtual void _set_shader_border(UShader&) = 0;
    virtual void _set_shader_point(UShader&)  = 0;

    // Members
    std::vector<UShader> m_shaders;
};

typedef std::unordered_map<std::string, std::shared_ptr<Cookable>> CookableCollection;
