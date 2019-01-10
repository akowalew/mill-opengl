#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace gkom {

class Camera
{
public:
	const glm::mat4& view() const;

	const glm::mat4& projection() const;

	const glm::vec3& position() const;

	void setPosition(const glm::vec3& position);

	const glm::vec3& centerPoint() const;

	void setCenterPoint(const glm::vec3& centerPoint);

	const glm::vec3& upAxis() const;

	void setUpAxis(const glm::vec3& upAxis);

	float fieldOfView() const;

	void setFieldOfView(float fieldOfView);

	float aspectRatio() const;

	void setAspectRatio(float aspectRatio);

	float nearPlane() const;

	void setNearPlane(float nearPlane);

	float farPlane() const;

	void setFarPlane(float farPlane);

private:
	glm::mat4 view_;
	glm::mat4 projection_;
	glm::vec3 position_;
	glm::vec3 centerPoint_;
	glm::vec3 upAxis_;
	float fieldOfView_;
	float aspectRatio_;
	float nearPlane_;
	float farPlane_;
};

} // gkom
