#include "gkom/VertexArray.hpp"

#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gkom {

VertexArray::VertexArray(unsigned int handle) noexcept
	:	handle_(handle)
{
	assert(handle_ != 0);
}

void VertexArray::bind()
{
	glBindVertexArray(handle_);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

bool VertexArray::isBound() const noexcept
{
	GLint currentBinding;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentBinding);
	return (static_cast<GLenum>(currentBinding) == handle_);
}

void VertexArray::enableAttribute(unsigned int attribute)
{
	assert(isBound());
	glEnableVertexAttribArray(attribute);
}

void VertexArray::disableAttribute(unsigned int attribute)
{
	assert(isBound());
	glDisableVertexAttribArray(attribute);
}

VertexArray::operator unsigned int() const noexcept
{
	return handle_;
}

} // gkom
