#pragma once

#include <cassert>
#include <cstdio>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gl {

class VertexBuffer
{
public:
	using Handle = GLuint;

	VertexBuffer(GLsizeiptr size, GLenum usage)
		:	handle(generateNative())
	{
		// Preconditions
		assert(handle);

		bind();
		reallocate(size, usage);
	}

	template<typename T, std::size_t N, std::size_t Size = sizeof(T) * N>
	VertexBuffer(const T (&array)[N], GLenum usage)
		:	VertexBuffer(Size, usage)
	{
		setData(0, Size, array);
	}

	~VertexBuffer()
	{
		if(handle)
		{
			puts("[GL] Deleting vertex buffer...");
			glDeleteBuffers(1, &handle);
		}
	}

	VertexBuffer(VertexBuffer&& other) noexcept
	{
		*this = std::move(other);
	}

	VertexBuffer& operator=(VertexBuffer&& other) noexcept
	{
		handle = other.handle;
		other.handle = Handle{};
		return *this;
	}

	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, handle);
	}

	void reallocate(GLsizeiptr size, GLenum usage)
	{
		// Preconditions
		assert(isBound());

		printf("[GL] Reallocating vertex buffer... Size: %ld Usage: %u\n", size, usage);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage);
	}

	void setData(GLintptr offset, GLsizeiptr size, const GLvoid* ptr)
	{
		// Preconditions
		assert(isBound());

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, ptr);
	}

	bool isBound() const noexcept
	{
		GLint currentBinding;
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentBinding);

		return (static_cast<GLenum>(currentBinding) == handle);
	}

	operator Handle() const noexcept { return handle; }

private:
	static Handle generateNative()
	{
		puts("[GL] Generating vertex buffer...");
		Handle handle;
		glGenBuffers(1, &handle);
		if(!handle)
		{
			throw std::runtime_error("Could not generate vertex array");
		}

		return handle;
	}

	Handle handle = Handle{};
};

} // gl
