#pragma once

#include <glm/glm.hpp>

#include "../Shaders/Shader.hpp"
#include "../../../Utils/Caster.hpp"

// Objects
struct Cookable : public Object {
    // Basic possibilities
    enum class CookType {
        Solid, Border, Point, Batch
    };

    // Instance
    virtual ~Cookable() = default;

    virtual Cookable* addRecipe(const CookType& type, const glm::vec4& color);

protected:
    // Vertices
    virtual void _set_shader_batch(UShader& shader);
    virtual void _set_shader_single(UShader& shader);

    // Geometry
    virtual void _set_shader_border(UShader&);
    virtual void _set_shader_point(UShader&);

    // Fragment
    virtual void _set_shader_light(UShader& shader);

    // Members
    std::vector<UShader> m_shaders;
};

typedef std::unordered_map<std::string, std::shared_ptr<Cookable>> CookableCollection;
