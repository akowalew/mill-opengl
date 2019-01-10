#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "gkom/Object.hpp"

namespace gkom {

class Shape
	:	public Object
{
public:
	const glm::mat4& model() const;

	const glm::vec3& position() const;

	void setPosition(const glm::vec3& position);

	const glm::vec3& rotation() const;

	void setRotation(const glm::vec3& rotation);

	const glm::vec3& scale() const;

	void setScale(const glm::vec3& scale);

private:
	glm::mat4 model_;
	glm::vec3 position_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
};

} // gkom
