#pragma once

#include "BaseShape.hpp"
#include "../Shaders/Shader.hpp"

// Shape 
struct Ellipse {
    // -------- Helper --------
    static void Draw(glm::vec3 pos, glm::vec2 size, glm::vec2 angles, glm::vec4 color);

private:
    // ---- Ellipse data ----
    Ellipse(glm::vec3 pos_, glm::vec2 size_, glm::vec4 color_);

    std::string _id() const;

    glm::vec3 m_pos;
    glm::vec2 m_size;
    glm::vec4 m_color;

    // Creating ellipse shape
    struct _Shape : public BaseShape {
        friend Ellipse;
        _Shape(float width, float height);

        void draw() override;
        void draw(int ptStart, int nPoints);

        void _setAttributes() override;

        // Helper
        static Shader& s_shader();
        static void _createShader();
    };

    // Creating and caching shapes
    static std::unique_ptr<_Shape>& _Get_Or_Create(const Ellipse& rectangle);
};