#pragma once

#include <glm/vec3.hpp>

namespace gkom {

struct Color : public glm::vec3
{
	Color()
		:	glm::vec3{0.0f, 0.0f, 0.0f}
	{}

	Color(const glm::vec3& col)
		:	glm::vec3{col}
	{}

	using glm::vec3::vec3;
};

} // gkom
