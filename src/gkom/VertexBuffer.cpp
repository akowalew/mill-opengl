#include "gkom/VertexBuffer.hpp"

#include <cstdio>
#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gkom {

VertexBuffer::VertexBuffer(unsigned int handle) noexcept
	:	handle_(handle)
{
	assert(handle != 0);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, handle_);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::reallocate(std::ptrdiff_t size)
{
	assert(isBound());
	const auto data = nullptr;
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void
VertexBuffer::loadSubData(std::ptrdiff_t offset, std::ptrdiff_t size,
						  const void* data)
{
	assert(isBound());
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void
VertexBuffer::loadData(std::ptrdiff_t size, const void *data)
{
	printf("%d\n", size);
	reallocate(size);

	const auto offset = 0;
	loadSubData(offset, size, data);
}

bool VertexBuffer::isBound() const noexcept
{
	GLint currentBinding;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentBinding);
	return (static_cast<GLenum>(currentBinding) == handle_);
}

VertexBuffer::operator unsigned int() const noexcept
{
	return handle_;
}

} // gkom
