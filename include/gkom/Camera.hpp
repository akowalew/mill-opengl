#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace gkom {

class Camera
{
public:
	glm::vec3 position {0.0f, 0.0f, 0.0f};
	glm::vec3 centerPoint {0.0f, 0.0f, 0.0f};
	glm::vec3 upAxis {0.0f, 0.0f, 1.0f};

	float fieldOfView {0.0f};
	float aspectRatio {0.0f};
	float nearPlane {0.0f};
	float farPlane {0.0f};

	glm::mat4 getView() const;

	glm::mat4 getProjection() const;
};

} // gkom
