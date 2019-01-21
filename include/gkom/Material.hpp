#pragma once

namespace gkom {

class Material
{
public:
	Material() = default;

	explicit Material(unsigned int shaderProgram)
		:	shaderProgram(shaderProgram)
	{}

	unsigned int shaderProgram {0};
};

} // gkom
