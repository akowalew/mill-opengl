#include "gkom/ConeFactory.hpp"

#include <cassert>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/trigonometric.hpp>

#include "gkom/GraphicsManager.hpp"
#include "gkom/Geometry.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

ConeFactory::ConeFactory(GraphicsManager& graphicsManager)
	:	graphicsManager_(graphicsManager)
	,	logger_(Logging::getLogger("ConeFactory"))
{
	logger_("Initialized");
}

ConeFactory::~ConeFactory() = default;

Geometry* ConeFactory::createCone(int sides)
{
	assert(sides >= 3); // At least triangle

	logger_("Looking for an existing cone geometry...");
	const auto cone = findCone(sides);
	if(cone != nullptr)
	{
		return cone;
	}

	logger_("Creating a new cone geometry...");
	const auto newConePos =
		cones_.emplace_hint(cones_.end(),
							std::make_pair(sides, makeCone(sides)));
	auto& newCone = newConePos->second;
	return &newCone;
}

Geometry* ConeFactory::findCone(int sides)
{
	const auto conePos = cones_.find(sides);
	if(conePos == cones_.end())
	{
		return nullptr;
	}

	return &(conePos->second);
}

Geometry ConeFactory::makeCone(int sides)
{
	assert(sides >= 3); // At least triangle

	// Generate vertices
	const auto angle = glm::radians(360.0f / sides);
	const auto corner = Vertex{{0.0f, 0.5f, 0.0f}};
	auto vertices = Vertices{corner}; // First point is the corner
	auto point = glm::vec3{-0.5f, -0.5f, 0.5f};
	for(auto i = 0; i < sides; ++i)
	{
		vertices.emplace_back(Vertex{point});
		point = glm::rotateY(point, angle);
	}

	// Generate indices
	auto indices = Indices{};
	for(unsigned int i = 1; i < sides; ++i)
	{
		// Insert next triangle
		indices.insert(indices.end(), {i, 0, i+1});
	}

	// Insert last triangle
	indices.insert(indices.end(), {static_cast<unsigned int>(sides), 0, 1});

	const auto vertexArray = graphicsManager_.createVertexArray(vertices,
																indices);
	const auto indicesCount = static_cast<int>(indices.size());
	return Geometry{vertexArray, indicesCount};
}

} // gkom
