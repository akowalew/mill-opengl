#include "gkom/PrismFactory.hpp"

#include <cassert>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/trigonometric.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "gkom/GeometryManager.hpp"
#include "gkom/Geometry.hpp"
#include "gkom/Logging.hpp"
#include "gkom/World.hpp"
#include "gkom/Entity.hpp"

namespace gkom {

	PrismFactory::PrismFactory(World& world, GeometryManager& geometryManager)
		: 	world_(world)
		,	geometryManager_(geometryManager)
		, logger_(Logging::getLogger("PrismFactory"))
	{
		logger_("Initialized");
	}

	PrismFactory::~PrismFactory() = default;

	Entity* PrismFactory::createPrism(int sides)
	{
		assert(sides >= 3); // At least triangle
		const auto entity = world_.createEntity();
		entity->geometry = makePrism(sides);
		return entity;
	}

	Geometry PrismFactory::makePrism(int sides)
	{
		assert(sides >= 3); // At least triangle

		std::vector<Vertex> vertices;

		const auto angle = glm::radians(360.0f / sides);
		auto lower = glm::vec3{ -0.5f, -0.5f, 0.5f };
		auto upper = glm::vec3{ -0.5f,  0.5f, 0.5f };
		auto normal = glm::rotateZ(glm::vec3{-1.0f, 0.0f, 0.0f}, glm::radians(-30.0f));
		normal = glm::rotateY(normal, angle/2);
		for(auto i = 0; i < sides; ++i)
		{
			const auto nextUpper = glm::rotateY(upper, angle);
			const auto nextLower = glm::rotateY(lower, angle);

			vertices.push_back(Vertex{lower, normal});
			vertices.push_back(Vertex{upper, normal});
			vertices.push_back(Vertex{nextUpper, normal});

			vertices.push_back(Vertex{nextUpper, normal});
			vertices.push_back(Vertex{nextLower, normal});
			vertices.push_back(Vertex{lower, normal});

			lower = nextLower;
			upper = nextUpper;
			normal = glm::rotateY(normal, angle);
		}

		return geometryManager_.createGeometry(vertices);
	}

} // gkom
