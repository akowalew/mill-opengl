#pragma once

#include <string_view>

namespace gkom {

//! Forward declarations
class Shader;
class Uniform;

class ShaderProgram
{
public:
	explicit ShaderProgram(unsigned int handle) noexcept;

	void attach(Shader shader);

	void detach(Shader shader);

	void link();

	bool isLinked() const noexcept;

	void use();

	void unuse();

	Uniform getUniform(std::string_view name);

	operator unsigned int() const noexcept;

private:
	unsigned int handle_;
};

} // gkom
