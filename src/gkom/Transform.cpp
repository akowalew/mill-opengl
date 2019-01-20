#include "gkom/Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace gkom {

glm::mat4 Transform::getMatrix() const
{
	return
		glm::rotate(
			glm::rotate(
				glm::rotate(
					glm::scale(
						glm::translate(glm::mat4{1.0f}, position),
						scale
					), rotation[0], glm::vec3{1.0f, 0.0f, 0.0f}
				), rotation[1], glm::vec3{0.0f, 1.0f, 0.0f}
			), rotation[2], glm::vec3{0.0f, 0.0f, 1.0f}
		);
}

} // gkom
