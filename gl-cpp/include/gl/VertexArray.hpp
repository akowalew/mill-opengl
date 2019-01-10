#pragma once

#include <cassert>
#include <cstdio>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gl {

class VertexArray
{
public:
	using Handle = GLuint;

	VertexArray()
		:	handle(generateNative())
	{
		// Preconditions
		assert(handle);

		bind();
	}

	~VertexArray()
	{
		if(handle)
		{
			puts("[GL] Deleting vertex array...");
			glDeleteVertexArrays(1, &handle);
		}
	}

	VertexArray(VertexArray&& other) noexcept
	{
		*this = std::move(other);
	}

	VertexArray& operator=(VertexArray&& other) noexcept
	{
		handle = other.handle;
		other.handle = Handle{};
		return *this;
	}

	void bind()
	{
		glBindVertexArray(handle);
	}

	bool isBound() const noexcept
	{
		GLint currentBinding;
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentBinding);

		return (static_cast<GLenum>(currentBinding) == handle);
	}

	operator Handle() const noexcept { return handle; }

private:
	static Handle generateNative()
	{
		puts("[GL] Generating vertex array...");
		Handle handle;
		glGenVertexArrays(1, &handle);
		if(!handle)
		{
			throw std::runtime_error("Could not generate vertex array");
		}

		return handle;
	}

	Handle handle = Handle{};
};

} // gl
