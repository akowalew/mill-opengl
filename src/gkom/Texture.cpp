#include "gkom/Texture.hpp"

#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gkom {

Texture::Texture(unsigned int handle) noexcept
	:	handle_(handle)
{}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, handle_);
}

void Texture::loadImage(int levelOfDetail, int width, int height,
			   			const unsigned char* data)
{
	assert(isBound());

	const auto internalFormat = GL_RGB;
	const auto format = GL_RGB;
	const auto type = GL_UNSIGNED_BYTE;
	const auto border = 0; // always zero
	glTexImage2D(GL_TEXTURE_2D, levelOfDetail, internalFormat,
		width, height, border, format, type, data);
}

void Texture::setParam(unsigned int name, int value)
{
	assert(isBound());

	glTexParameteri(GL_TEXTURE_2D, name, value);
}

void Texture::setParam(unsigned int name, float value)
{
	assert(isBound());

	glTexParameterf(GL_TEXTURE_2D, name, value);
}

bool Texture::isBound() const noexcept
{
	GLint currentBinding;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentBinding);

	return (static_cast<GLenum>(currentBinding) == handle_);
}

Texture::operator unsigned int() const noexcept
{
	return handle_;
}

} // gkom
