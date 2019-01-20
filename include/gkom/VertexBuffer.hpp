#pragma once

#include <cstdint>
#include <vector>

namespace gkom {

class VertexBuffer
{
public:
	VertexBuffer(unsigned int handle) noexcept;

	void bind();

	void unbind();

	void reallocate(std::ptrdiff_t size);

	void loadSubData(std::ptrdiff_t offset, std::ptrdiff_t size,
				  	 const void* data);

	void loadData(std::ptrdiff_t size, const void* data);

	template<typename T>
	void loadData(const std::vector<T>& vertices);

	bool isBound() const noexcept;

	operator unsigned int() const noexcept;

private:
	unsigned int handle_;
};

template<typename T>
void VertexBuffer::loadData(const std::vector<T>& vertices)
{
	const auto size = (sizeof(T) * vertices.size());
	loadData(size, vertices.data());
}

} // gkom
