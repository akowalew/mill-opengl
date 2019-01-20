#pragma once

#include <cstdint>
#include <vector>

namespace gkom {

class IndexBuffer
{
public:
	IndexBuffer(unsigned int handle) noexcept;

	void bind();

	void unbind();

	void reallocate(std::ptrdiff_t size);

	void loadSubData(std::ptrdiff_t offset, std::ptrdiff_t size,
				  	 const void* data);

	void loadData(std::ptrdiff_t size, const void* data);

	template<typename T>
	void loadData(const std::vector<T>& indices);

	bool isBound() const noexcept;

	operator unsigned int() const noexcept;

private:
	unsigned int handle_;
};

template<typename T>
void IndexBuffer::loadData(const std::vector<T>& indices)
{
	const auto size = (sizeof(T) * indices.size());
	loadData(size, indices.data());
}

} // gkom
