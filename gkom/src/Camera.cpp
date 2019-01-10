#include "gkom/Camera.hpp"

namespace gkom {

const glm::mat4& Camera::view() const
{
	return view_;
}

const glm::mat4& Camera::projection() const
{
	return projection_;
}

const glm::vec3& Camera::position() const
{
	return position_;
}

void Camera::setPosition(const glm::vec3& position)
{
	position_ = position;
}

const glm::vec3& Camera::centerPoint() const
{
	return centerPoint_;
}

void Camera::setCenterPoint(const glm::vec3& centerPoint)
{
	centerPoint_ = centerPoint;
}

const glm::vec3& Camera::upAxis() const
{
	return upAxis_;
}

void Camera::setUpAxis(const glm::vec3& upAxis)
{
	upAxis_ = upAxis;
}

float Camera::fieldOfView() const
{
	return fieldOfView_;
}

void Camera::setFieldOfView(float fieldOfView)
{
	fieldOfView_ = fieldOfView;
}

float Camera::aspectRatio() const
{
	return aspectRatio_;
}

void Camera::setAspectRatio(float aspectRatio)
{
	aspectRatio_ = aspectRatio;
}

float Camera::nearPlane() const
{
	return nearPlane_;
}

void Camera::setNearPlane(float nearPlane)
{
	nearPlane_ = nearPlane;
}

float Camera::farPlane() const
{
	return farPlane_;
}

void Camera::setFarPlane(float farPlane)
{
	farPlane_ = farPlane;
}

} // gkom
