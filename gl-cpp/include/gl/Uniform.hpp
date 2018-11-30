#pragma once

#include <cstdio>
#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl {

class Uniform
{
public:
	using Location = GLint;

	explicit Uniform(Location location)
		:	location(location)
	{
		// Preconditions
		assert(location != -1);
	}

	void setValue(GLfloat v0)
	{
		glUniform1f(location, v0);
	}

	void setValue(GLfloat v0, GLfloat v1)
	{
		glUniform2f(location, v0, v1);
	}

	void setValue(GLfloat v0, GLfloat v1, GLfloat v2)
	{
		glUniform3f(location, v0, v1, v2);
	}

	void setValue(GLint v0)
	{
		glUniform1i(location, v0);
	}

	void setValue(GLint v0, GLint v1)
	{
		glUniform2i(location, v0, v1);
	}

	void setValue(GLint v0, GLint v1, GLint v2)
	{
		glUniform3i(location, v0, v1, v2);
	}

	void setValue(const glm::mat4& v, GLboolean transpose)
	{
		glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(v));
	}

	operator Location() const noexcept { return location; }

private:
	Location location;
};

} // gl
