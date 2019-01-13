#include "gkom/Mesh.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace gkom {

glm::mat4 Mesh::getModelMatrix() const
{
   	return glm::scale(
        glm::translate(glm::mat4(1.0f), position),
        scale
    );
}

} // gkom
