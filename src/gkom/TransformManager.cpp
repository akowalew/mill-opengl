#include "gkom/TransformManager.hpp"

#include <cassert>

#include "gkom/Logging.hpp"
#include "gkom/Transform.hpp"

namespace gkom {

TransformManager::TransformManager()
	:	logger_(Logging::getLogger("TransformManager"))
{
	logger_("Initialized");
}

TransformManager::~TransformManager() = default;

Transform*
TransformManager::createTransform()
{
	auto& transform =
		transforms_.emplace_back(std::make_unique<Transform>(1.0f));
	assert(transform);
	return transform.get();
}

Transform*
TransformManager::createTransform(const glm::mat4& tf)
{
	auto& transform =
		transforms_.emplace_back(std::make_unique<Transform>(tf));
	assert(transform);
	return transform.get();
}

} // gkom
