#include "gkom/IndexBuffer.hpp"

#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gkom {

IndexBuffer::IndexBuffer(unsigned int handle) noexcept
	:	handle_(handle)
{
	assert(handle_ != 0);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::reallocate(std::ptrdiff_t size)
{
	assert(isBound());
	const auto data = nullptr;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBuffer::loadSubData(std::ptrdiff_t offset,
							  std::ptrdiff_t size,
						   	  const void* data)
{
	assert(isBound());
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
}

void IndexBuffer::loadData(std::ptrdiff_t size, const void* data)
{
	reallocate(size);

	const auto offset = 0;
	loadSubData(offset, size, data);
}

bool IndexBuffer::isBound() const noexcept
{
	GLint currentBinding;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentBinding);
	return (static_cast<GLenum>(currentBinding) == handle_);
}

IndexBuffer::operator unsigned int() const noexcept
{
	return handle_;
}

} // gkom
