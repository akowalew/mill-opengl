#pragma once

namespace gkom {

class Texture
{
public:
	explicit Texture(unsigned int handle) noexcept;

	void bind();

	void loadImage(int levelOfDetail, int width, int height,
				   const unsigned char* data);

	void setParam(unsigned int name, int value);

	void setParam(unsigned int name, float value);

	bool isBound() const noexcept;

	operator unsigned int() const noexcept;

private:
	unsigned int handle_;
};

} // gkom
