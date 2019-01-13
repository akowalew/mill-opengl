#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace gkom {

class Mesh
{
public:
	glm::vec3 position;
	glm::vec3 scale;

	glm::mat4 getModelMatrix() const;
};

} // gkom
