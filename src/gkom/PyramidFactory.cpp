#include "gkom/PyramidFactory.hpp"

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

PyramidFactory::PyramidFactory(World& world, GeometryManager& geometryManager)
	:	world_(world)
	,	geometryManager_(geometryManager)
	,	logger_(Logging::getLogger("PyramidFactory"))
{
	logger_("Initialized");
}

PyramidFactory::~PyramidFactory() = default;

Entity* PyramidFactory::createPyramid()
{
	auto entity = world_.createEntity();

	if(!pyramid_)
	{
		pyramid_ = makePyramid();
	}

	entity->geometry = *pyramid_;
	return entity;
}

std::unique_ptr<Geometry> PyramidFactory::makePyramid()
{
	logger_("Making new pyramid geometry...");
	const auto vertices = makeVertices();
	const auto geometry = geometryManager_.createGeometry(vertices);
	return std::make_unique<Geometry>(geometry);
}

std::vector<Vertex> PyramidFactory::makeVertices()
{
	return {
    	{{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},
     	{{ 0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},
     	{{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
     	{{ 0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
    	{{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
    	{{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},

    	{{-0.5f, -0.5f, -0.5f}, glm::rotateZ(glm::vec3{-1.0f, 0.0f, 0.0f}, glm::radians(-30.0f))},
    	{{ 0.0f,  0.5f,  0.0f}, glm::rotateZ(glm::vec3{-1.0f, 0.0f, 0.0f}, glm::radians(-30.0f))},
    	{{-0.5f, -0.5f,  0.5f}, glm::rotateZ(glm::vec3{-1.0f, 0.0f, 0.0f}, glm::radians(-30.0f))},

    	{{ 0.5f, -0.5f, -0.5f}, glm::rotateZ(glm::vec3{1.0f, 0.0f, 0.0f}, glm::radians(30.0f))},
    	{{ 0.0f,  0.5f,  0.0f}, glm::rotateZ(glm::vec3{1.0f, 0.0f, 0.0f}, glm::radians(30.0f))},
    	{{ 0.5f, -0.5f,  0.5f}, glm::rotateZ(glm::vec3{1.0f, 0.0f, 0.0f}, glm::radians(30.0f))},

    	{{-0.5f, -0.5f, -0.5f}, glm::rotateX(glm::vec3{0.0f, 0.0f, -1.0f}, glm::radians(30.0f))},
    	{{ 0.0f,  0.5f,  0.0f}, glm::rotateX(glm::vec3{0.0f, 0.0f, -1.0f}, glm::radians(30.0f))},
    	{{ 0.5f, -0.5f, -0.5f}, glm::rotateX(glm::vec3{0.0f, 0.0f, -1.0f}, glm::radians(30.0f))},

    	{{-0.5f, -0.5f,  0.5f}, glm::rotateX(glm::vec3{0.0f, 0.0f, 1.0f}, glm::radians(-30.0f))},
    	{{ 0.0f,  0.5f,  0.0f}, glm::rotateX(glm::vec3{0.0f, 0.0f, 1.0f}, glm::radians(-30.0f))},
    	{{-0.5f, -0.5f,  0.5f}, glm::rotateX(glm::vec3{0.0f, 0.0f, 1.0f}, glm::radians(-30.0f))},
	};
}

} // gkom
