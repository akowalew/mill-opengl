#include "gkom/World.hpp"

#include "gkom/Logging.hpp"
#include "gkom/Entity.hpp"

namespace gkom {

World::World()
	:	logger_(Logging::getLogger("World"))
{
	logger_("Initialized");
}

World::~World() = default;

Entity* World::createEntity()
{
	logger_("Creating new entity...");

	const auto& entity = entities.emplace_back(std::make_unique<Entity>());
	assert(entity != nullptr);
	return entity.get();
}

void World::clear()
{
	entities.clear();
}

} // gkom
