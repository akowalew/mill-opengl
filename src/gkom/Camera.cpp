#include "gkom/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace gkom {

glm::mat4 Camera::getView() const
{
	return glm::lookAt(position, centerPoint, upAxis);
}

glm::mat4 Camera::getProjection() const
{
	return glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
}

} // gkom
