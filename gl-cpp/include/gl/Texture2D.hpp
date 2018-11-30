#pragma once

#include <cassert>
#include <cstdio>
#include <stdexcept>
#include <memory>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SOIL.h>

namespace gl {

class Texture2D
{
public:
	using Handle = GLuint;

	Texture2D(GLenum unit = GL_TEXTURE0)
		:	handle(generateNative())
		,	unit(unit)
	{
		// Preconditions
		assert(handle);

		bind();
	}

	Texture2D(GLint level, GLint internalFormat,
		      GLsizei width, GLsizei height, GLenum format,
		      GLenum type, const GLvoid* data,
		      GLenum unit = GL_TEXTURE0)
		:	Texture2D(unit)
	{
		setImage(level, internalFormat, width, height, format, type, data);
	}

	explicit Texture2D(const char* path, GLenum unit = GL_TEXTURE0)
		:	Texture2D(unit)
	{
		// Preconditions
		assert(path);

		printf("[GL] Loading texture 2D from file... Path: '%s'\n", path);

	    int width, height;
	   	auto imageData = std::unique_ptr<unsigned char>(
	   		SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB));
	   	if(!imageData)
	   	{
	   		throw std::runtime_error("Could not load 2D image data");
	   	}

	   	const auto level = 0;
	   	const auto internalFormat = GL_RGB;
	   	const auto format = GL_RGB;
	   	const auto type = GL_UNSIGNED_BYTE;
	    setImage(level, internalFormat, width, height, format, type, imageData.get());
	}

	~Texture2D()
	{
		if(handle)
		{
			puts("[GL] Deleting texture...");
			glDeleteTextures(1, &handle);
		}
	}

	Texture2D(Texture2D&& other) noexcept
	{
		*this = std::move(other);
	}

	Texture2D& operator=(Texture2D&& other) noexcept
	{
		handle = other.handle;
		other.handle = Handle{};
		return *this;
	}

	void bind()
	{
		glActiveTexture(unit);
		glBindTexture(GL_TEXTURE_2D, handle);

		// Postconditions
		assert(isBound());
	}

	void setImage(GLint level, GLint internalFormat,
		       GLsizei width, GLsizei height, GLenum format,
		       GLenum type, const GLvoid* data)
	{
		// Preconditions
		assert(isBound());

		const auto border = 0; // always zero
		glTexImage2D(GL_TEXTURE_2D, level, internalFormat,
			width, height, border, format, type, data);
	}

	void setParam(GLenum name, GLint value)
	{
		// Preconditions
		assert(isBound());

		glTexParameteri(GL_TEXTURE_2D, name, value);
	}

	void setParams(std::initializer_list<std::pair<GLenum /*name*/, GLint /*value*/>> params)
	{
		for(const auto [name, value]: params)
		{
			setParam(name, value);
		}
	}

	bool isBound() const noexcept
	{
		GLint currentBinding;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentBinding);

		return (static_cast<GLenum>(currentBinding) == handle);
	}

	operator Handle() const noexcept { return handle; }

private:
	static Handle generateNative()
	{
		puts("[GL] Generating texture...");
		Handle handle;
		glGenTextures(1, &handle);
		if(!handle)
		{
			throw std::runtime_error("Could not generate texture");
		}

		return handle;
	}

	Handle handle = Handle{};
	GLenum unit;
};

} // gl
