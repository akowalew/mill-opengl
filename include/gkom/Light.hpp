#pragma once

#include <glm/vec3.hpp>

namespace gkom {

//! Component
struct Light
{
	Light() = default;

	explicit Light(const glm::vec3& color)
		:	color(color)
	{}

	glm::vec3 color;
};

} // gkom
