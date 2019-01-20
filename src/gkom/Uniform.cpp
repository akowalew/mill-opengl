#include "gkom/Uniform.hpp"

#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

namespace gkom {

Uniform::Uniform(int location) noexcept
	:	location_(location)
{
	assert(location_ != -1);
}

void Uniform::loadValue(float v0)
{
	glUniform1f(location_, v0);
}

void Uniform::loadValue(float v0, float v1)
{
	glUniform2f(location_, v0, v1);
}

void Uniform::loadValue(float v0, float v1, float v2)
{
	glUniform3f(location_, v0, v1, v2);
}

void Uniform::loadValue(float v0, float v1, float v2, float v3)
{
	glUniform4f(location_, v0, v1, v2, v3);
}

void Uniform::loadValue(const glm::vec2& v)
{
	const auto count = 1;
	glUniform2fv(location_, count, glm::value_ptr(v));
}

void Uniform::loadValue(const glm::vec3& v)
{
	const auto count = 1;
	glUniform3fv(location_, count, glm::value_ptr(v));
}

void Uniform::loadValue(const glm::vec4& v)
{
	const auto count = 1;
	glUniform4fv(location_, count, glm::value_ptr(v));
}

void Uniform::loadValue(int v0)
{
	glUniform1i(location_, v0);
}

void Uniform::loadValue(int v0, int v1)
{
	glUniform2i(location_, v0, v1);
}

void Uniform::loadValue(int v0, int v1, int v2)
{
	glUniform3i(location_, v0, v1, v2);
}

void Uniform::loadValue(int v0, int v1, int v2, int v3)
{
	glUniform4i(location_, v0, v1, v2, v3);
}

void Uniform::loadValue(unsigned int v0)
{
	glUniform1ui(location_, v0);
}

void Uniform::loadValue(unsigned int v0, unsigned int v1)
{
	glUniform2ui(location_, v0, v1);
}

void Uniform::loadValue(unsigned int v0, unsigned int v1, unsigned int v2)
{
	glUniform3ui(location_, v0, v1, v2);
}

void Uniform::loadValue(unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
{
	glUniform4ui(location_, v0, v1, v2, v3);
}

void Uniform::loadMatrix(const glm::mat3& v)
{
	const auto transpose = false;
	const auto count = 1;
	glUniformMatrix3fv(location_, count, transpose, glm::value_ptr(v));
}

void Uniform::loadMatrix(const glm::mat4& v)
{
	const auto transpose = false;
	const auto count = 1;
	glUniformMatrix4fv(location_, count, transpose, glm::value_ptr(v));
}

Uniform::operator int() const noexcept
{
	return location_;
}

} // gkom
