#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "BaseShape.hpp"
#include "../Shaders/Shader.hpp"

#include <memory>

struct BaseDrawable {
	virtual ~BaseDrawable() = default;

	// Sub Helpers
	struct DrawData {
		glm::vec3 pos;
		glm::vec2 size;
		glm::vec4 color;
	} m_data;

	struct Shape : public BaseShape {
		Shape(const glm::vec2&) {};

		void draw() override {};
		void _setAttributes() override {};

		// Helper
		static Shader& s_shader() {};
		static void _createShader() {};
	};

	// Methods
	static void Draw(const DrawData& data) {};


protected:
	BaseDrawable(const DrawData& data) : m_data(data) {};

	virtual std::string id() const {
		return std::to_string(m_data.size.x) + "." + std::to_string(m_data.size.y);
	};

private:
	// Creating and caching shapes
	static std::unique_ptr<BaseShape>& _Get_Or_Create(const BaseDrawable& rectangle) {};

};
