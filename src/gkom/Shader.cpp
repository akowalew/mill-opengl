#include "gkom/Shader.hpp"

#include <cassert>
#include <vector>
#include <stdexcept>
#include <cstdio>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gkom {

Shader::Shader(unsigned int handle) noexcept
	:	handle_(handle)
{
	assert(handle_ != 0);
}

void
Shader::loadSource(const char* string, const int length)
{
	const auto count = 1;
	const auto strings = &string;
	const auto lengths = &length;
	loadSources(count, strings, lengths);
}

void
Shader::loadSources(int count, const char** strings, const int* lengths)
{
	glShaderSource(handle_, count, strings, lengths);
}

void
Shader::compile()
{
	using namespace std::string_literals;

	glCompileShader(handle_);

	GLint compiled;
	glGetShaderiv(handle_, GL_COMPILE_STATUS, &compiled);
	if(compiled != GL_TRUE)
	{
	    GLsizei logLength = 0;
		glGetShaderiv(handle_, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<GLchar> log(logLength);
	    glGetShaderInfoLog(handle_, log.max_size(), nullptr, log.data());
	    throw std::runtime_error("Could not compile shader: "s
	    						 + std::string(log.data(), logLength));
	}
}

bool
Shader::isCompiled() const noexcept
{
	GLint compiled;
	glGetShaderiv(handle_, GL_COMPILE_STATUS, &compiled);
	return (compiled == GL_TRUE);
}

Shader::operator unsigned int() const noexcept
{
	return handle_;
}

} // gkom
