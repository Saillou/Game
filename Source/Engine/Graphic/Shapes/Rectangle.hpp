#pragma once

#include "BaseShape.hpp"
#include "../Shaders/Shader.hpp"

// Shape 
struct Rectangle {
    // -------- Helper --------
    static void Draw(glm::vec3 pos, glm::vec2 size, glm::vec4 color);

private:
    // ---- Rectangle data ----
    Rectangle(glm::vec3 pos_, glm::vec2 size_, glm::vec4 color_);

    std::string _id() const;

    glm::vec3 m_pos;
    glm::vec2 m_size;
    glm::vec4 m_color;

    // Creating and caching shapes
    static std::unique_ptr<BaseShape>& _Get_Or_Create(const Rectangle& rectangle);

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
