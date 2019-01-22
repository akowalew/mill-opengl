#include "gkom/LightFactory.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/trigonometric.hpp>
#include <glm/gtx/transform.hpp>

#include "gkom/World.hpp"
#include "gkom/Entity.hpp"
#include "gkom/Logging.hpp"
#include "gkom/Light.hpp"

namespace gkom {

LightFactory::LightFactory(World& world)
	:	world_(world)
	,	logger_(Logging::getLogger("LightFactory"))
{
	logger_("Initialized");
}

LightFactory::~LightFactory() = default;

Entity* LightFactory::createLight(const glm::vec3& position,
								  const glm::vec3& color)
{
	logger_("Creating light for given position and color...");
	const auto light = world_.createEntity();
	assert(light != nullptr);

	light->light = Light{color};
	light->transform = glm::translate(position);
	return light;
}

} // gkom
