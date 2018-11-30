#pragma once

#include <cassert>
#include <cstdio>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gl {

class ElementBuffer
{
public:
	using Handle = GLuint;

	ElementBuffer(GLsizeiptr size, GLenum usage)
		:	handle(generateNative())
	{
		// Preconditions
		assert(handle);

		bind();
		reallocate(size, usage);
	}

	template<typename T, std::size_t N, std::size_t Size = sizeof(T) * N>
	ElementBuffer(const T (&array)[N], GLenum usage)
		:	ElementBuffer(Size, usage)
	{
		static_assert(std::is_same_v<T, GLuint>
			          	|| std::is_same_v<T, GLushort>
			          		|| std::is_same_v<T, GLubyte>,
			          "Data for element buffer must be an array of GLuint, GLushort or GLubyte");

		setData(0, Size, array);
	}

	~ElementBuffer()
	{
		if(handle)
		{
			puts("[GL] Deleting array buffer...");
			glDeleteBuffers(1, &handle);
		}
	}

	ElementBuffer(ElementBuffer&& other) noexcept
	{
		*this = std::move(other);
	}

	ElementBuffer& operator=(ElementBuffer&& other) noexcept
	{
		handle = other.handle;
		other.handle = Handle{};
		return *this;
	}

	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
	}

	void reallocate(GLsizeiptr size, GLenum usage)
	{
		// Preconditions
		assert(isBound());

		printf("[GL] Reallocating element buffer... Size: %ld Usage: %u\n", size, usage);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, usage);
	}

	void setData(GLintptr offset, GLsizeiptr size, const GLvoid* ptr)
	{
		// Preconditions
		assert(isBound());

		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, ptr);
	}

	bool isBound() const noexcept
	{
		GLint currentBinding;
		glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentBinding);

		return (static_cast<GLenum>(currentBinding) == handle);
	}

	operator Handle() const noexcept { return handle; }

private:
	static Handle generateNative()
	{
		puts("[GL] Generating element buffer...");
		Handle handle;
		glGenBuffers(1, &handle);
		if(!handle)
		{
			throw std::runtime_error("Could not generate vertex element");
		}

		return handle;
	}

	Handle handle = Handle{};
};

} // gl
