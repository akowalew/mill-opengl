#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace gkom {

class Transform
{
public:
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;

	glm::mat4 getMatrix() const;
};

} // gkom
