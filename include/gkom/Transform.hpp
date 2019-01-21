#pragma once

#include <glm/mat4x4.hpp>

namespace gkom {

struct Transform : public glm::mat4
{
	Transform()
		:	glm::mat4(1.0f)
	{}

	using glm::mat4::mat4;

	Transform(const glm::mat4& tf)
		: glm::mat4(tf)
	{}
};

} // gkom
