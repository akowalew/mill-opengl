#pragma once

namespace gkom {

class VertexArray
{
public:
	VertexArray(unsigned int handle) noexcept;

	void bind();

	void unbind();

	bool isBound() const noexcept;

	void enableAttribute(unsigned int attribute);

	void disableAttribute(unsigned int attribute);

	operator unsigned int() const noexcept;

private:
	unsigned int handle_;
};

} // gkom
