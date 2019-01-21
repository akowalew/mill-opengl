#include "gkom/LightManager.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/trigonometric.hpp>
#include <glm/gtx/transform.hpp>

#include "gkom/World.hpp"
#include "gkom/Entity.hpp"
#include "gkom/ColorFactory.hpp"
#include "gkom/TransformManager.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

LightManager::LightManager(World& world,
						   TransformManager& transformManager,
						   ColorFactory& colorFactory)
	:	world_(world)
	,	transformManager_(transformManager)
	,	colorFactory_(colorFactory)
	,	logger_(Logging::getLogger("LightManager"))
{
	logger_("Initialized");
}

LightManager::~LightManager() = default;

Entity* LightManager::createLight(const glm::vec3& position,
								  const glm::vec3& col)
{
	logger_("Creating light node for given position and color...");

	const auto light = world_.createEntity();
	assert(light != nullptr);

	const auto transform = transformManager_.createTransform(
		glm::translate(position));
	assert(transform != nullptr);

	const auto color = colorFactory_.createColor(col);
	assert(color != nullptr);

	light->color = color;
	light->transform = transform;
	return light;
}

const std::vector<Entity*>& LightManager::lights() const
{
	return lights_;
}

} // gkom
