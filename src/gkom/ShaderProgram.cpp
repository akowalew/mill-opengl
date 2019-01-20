#include "gkom/ShaderProgram.hpp"

#include <cassert>
#include <vector>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

#include "gkom/Shader.hpp"
#include "gkom/Uniform.hpp"

namespace gkom {

ShaderProgram::ShaderProgram(unsigned int handle) noexcept
	:	handle_(handle)
{
	assert(handle_ != 0);
}

void ShaderProgram::attach(Shader shader)
{
	glAttachShader(handle_, shader);
}

void ShaderProgram::detach(Shader shader)
{
	glDetachShader(handle_, shader);
}

void ShaderProgram::link()
{
	using namespace std::string_literals;

	glLinkProgram(handle_);

	GLint linked;
	glGetProgramiv(handle_, GL_LINK_STATUS, &linked);
	if(!linked)
	{
	    GLsizei logLength = 0;
		glGetProgramiv(handle_, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<GLchar> log(logLength);
	    glGetProgramInfoLog(handle_, log.size(), nullptr, log.data());
	    throw std::runtime_error("Could not link program, reason: "s
	    						 + std::string(log.data(), logLength));
	}
}

bool
ShaderProgram::isLinked() const noexcept
{
	GLint linked;
	glGetProgramiv(handle_, GL_LINK_STATUS, &linked);
	return (linked == GL_TRUE);
}

void
ShaderProgram::use()
{
	glUseProgram(handle_);
}

void
ShaderProgram::unuse()
{
	glUseProgram(0);
}

Uniform ShaderProgram::getUniform(std::string_view name)
{
	using namespace std::string_literals;

	const auto location = glGetUniformLocation(handle_, name.data());
	if(location == -1)
	{
		throw std::runtime_error("Could not get location of uniform: "s
								 + name.data());
	}

	return Uniform{location};
}

ShaderProgram::operator unsigned int() const noexcept
{
	return handle_;
}

} // gkom
