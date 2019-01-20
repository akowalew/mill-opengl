#pragma once

#include <glm/vec4.hpp>

namespace gkom {

class Material
{
public:
	Material(const glm::vec4& color,
			 unsigned int shaderProgram)
		:	color(color)
		,	shaderProgram(shaderProgram)
	{}

	glm::vec4 color;
	unsigned int shaderProgram {0};
};

} // gkom
