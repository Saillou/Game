#pragma once

#include "../../../Engine/Graphic/Drawables/BaseDrawable.hpp"
#include "../../../Engine/Graphic/Drawables/BaseShape.hpp"
#include "../../../Engine/Graphic/Shaders/Shader.hpp"

// Shape 
struct Ellipse : public BaseDrawable {
    // -------- Helper --------
    static void Draw(glm::vec3 pos, glm::vec2 size, glm::vec2 angles, glm::vec4 color);

private:
    // ---- Ellipse data ----
    Ellipse(glm::vec3 pos_, glm::vec2 size_, glm::vec4 color_);

    std::string id() const;

    glm::vec3 m_pos;
    glm::vec2 m_size;
    glm::vec4 m_color;

    // Creating ellipse shape
    struct _Shape : public BaseShape {
        _Shape(float width, float height);

        void draw() override;
        void draw(int ptStart, int nPoints);
        void _setAttributes() override;

        // Helper
        static Shader& s_shader();
        static void _createShader();
    };
};
