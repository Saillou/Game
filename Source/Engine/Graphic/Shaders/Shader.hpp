#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>

#include "ShaderSource.hpp"

class Shader
{
public:
	Shader();
	virtual ~Shader();

	Shader& operator=(const Shader&)	= delete;
	Shader(const Shader&)				= delete;
	Shader(Shader&&)					= delete;

	// First, use on of these:
	void attachSource(const unsigned int shader_type, const std::string& shaderCode);
	void attachFile(const unsigned int shader_type, const std::string& shaderPath);

	// Then, after attached:
	void link();
	void use();

	void set(const std::string& name, float v);
	void set(const std::string& name, float a, float b, float c);
	void set(const std::string& name, const glm::mat3& mat);
	void set(const std::string& name, const glm::mat4& mat);
	void setBlock(const std::string& name, const int layout);

	unsigned int getId() const;

private:
	static const std::string _readFromFile(const std::string& path);

	unsigned int m_id;
};

typedef std::unique_ptr<Shader> UShader;