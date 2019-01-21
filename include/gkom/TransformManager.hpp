#pragma once

#include <memory>
#include <vector>

#include <glm/mat4x4.hpp>

namespace gkom {

//! Forward declarations
class Transform;
class Logger;

class TransformManager
{
public:
	TransformManager();

	~TransformManager();

	Transform* createTransform();

	Transform* createTransform(const glm::mat4& tf);

private:
	std::vector<std::unique_ptr<Transform>> transforms_;
	Logger& logger_;
};

} // gkom
