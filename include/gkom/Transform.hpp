#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace gkom {

class Transform
{
public:
	glm::vec3 position {0.0f, 0.0f, 0.0f};
	glm::vec3 scale {1.0f, 1.0f, 1.0f};
	glm::vec3 rotation {0.0f, 0.0f, 0.0f};

	glm::mat4 getMatrix() const;
};

} // gkom
