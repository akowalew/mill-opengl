#pragma once

#include "gkom/Shader.hpp"

namespace gkom {

class Shader
{
public:
	explicit Shader(unsigned int handle) noexcept;

	void loadSource(const char* string, const int length);

	void loadSources(int count, const char** strings, const int* lengths);

	void compile();

	bool isCompiled() const noexcept;

	operator unsigned int() const noexcept;

private:
	unsigned int handle_;
};

} // gkom
