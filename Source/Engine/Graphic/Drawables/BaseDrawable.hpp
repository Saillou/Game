#pragma once

#include <memory>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "BaseShape.hpp"
#include "../Shaders/Shader.hpp"


struct BaseDrawable {
	virtual ~BaseDrawable() = default;

protected:
	BaseDrawable() = default;
	virtual std::string id() const = 0; // Define an identifier for the shape created

	// Creating and caching shapes
	typedef std::function<std::shared_ptr<BaseShape>(void)> ShapeCreator;

	static std::shared_ptr<BaseShape> _Get_Or_Create(ShapeCreator creator, const std::string& id);
};
