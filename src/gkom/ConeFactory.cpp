#include "gkom/ConeFactory.hpp"

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

	ConeFactory::ConeFactory(World& world, GeometryManager& geometryManager)
		: 	world_(world)
		,	geometryManager_(geometryManager)
		, logger_(Logging::getLogger("ConeFactory"))
	{
		logger_("Initialized");
	}

	ConeFactory::~ConeFactory() = default;

	Entity* ConeFactory::createCone(int sides)
	{
		assert(sides >= 3); // At least triangle
		const auto entity = world_.createEntity();
		entity->geometry = makeCone(sides);
		return entity;
	}

	Geometry ConeFactory::makeCone(int sides)
	{
		assert(sides >= 3); // At least triangle

		std::vector<Vertex> vertices;

		auto corner = glm::vec3{ 0.0f, 0.5f, 0.0f};
		const auto angle = glm::radians(360.0f / sides);
		auto point = glm::vec3{ -0.5f, -0.5f, 0.5f };
		auto normal = glm::rotateZ(glm::vec3{-1.0f, 0.0f, 0.0f}, glm::radians(-30.0f));
		normal = glm::rotateY(normal, -angle/2);
		for(auto i = 0; i < sides; ++i)
		{
			vertices.push_back(Vertex{point, normal});
			vertices.push_back(Vertex{corner, normal});

			point = glm::rotateY(point, angle);

			vertices.push_back(Vertex{point, normal});

			normal = glm::rotateY(normal, angle);
		}

		return geometryManager_.createGeometry(vertices);
	}

} // gkom
