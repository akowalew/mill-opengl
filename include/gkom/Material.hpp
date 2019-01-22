#pragma once

#include <glm/vec3.hpp>

#include "gkom/ShaderProgram.hpp"

namespace gkom {

//! Component
struct Material
{
public:
	Material() = default;

	explicit Material(ShaderProgram shaderProgram,
					  const glm::vec3& color)
		:	shaderProgram(shaderProgram)
		,	color(color)
	{}

	ShaderProgram shaderProgram;
	glm::vec3 color {0.0f, 0.0f, 0.0f};
};

} // gkom
