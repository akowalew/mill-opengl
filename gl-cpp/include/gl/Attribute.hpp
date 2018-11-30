#pragma once

#include <cstdio>
#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gl {

class Attribute
{
public:
	using Location = GLint;

	explicit Attribute(Location location)
		:	location(location)
	{
		// Preconditions
		assert(location != -1);
	}

	void enable()
	{
		glEnableVertexAttribArray(location);
	}

	void disable()
	{
		glDisableVertexAttribArray(location);
	}

	void setFormat(GLint size, GLenum type, GLboolean normalized,
		           GLsizei stride = 0, std::size_t offset = 0)
	{
		puts("[GL] Setting data format for an attribute...");
		glVertexAttribPointer(location, size, type, normalized, stride, (void*)offset);
	}

	operator Location() const noexcept { return location; }

private:
	Location location;
};

} // gl
