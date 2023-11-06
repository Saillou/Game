#pragma once

#include "BaseShape.hpp"
#include "BaseDrawable.hpp"
#include "../Shaders/Shader.hpp"

// Shape 
struct Rectangle : public BaseDrawable {
    // -------- Helper --------
    static void Draw(glm::vec3 pos, glm::vec2 size, glm::vec4 color);

protected:
    std::string id() const override;

private:
    // ---- Rectangle data ----
    Rectangle(glm::vec3 pos_, glm::vec2 size_, glm::vec4 color_);


    glm::vec3 m_pos;
    glm::vec2 m_size;
    glm::vec4 m_color;

    // Creating rectangle shape
    struct _Shape : public BaseShape {
        _Shape(float width, float height);

        void draw() override;
        void _setAttributes() override;

        // Helper
        static Shader& s_shader();
        static void _createShader();
    };
};
