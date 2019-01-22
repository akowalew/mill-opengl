#include "gkom/BoxFactory.hpp"

#include <cassert>

#include "gkom/GeometryManager.hpp"
#include "gkom/Geometry.hpp"
#include "gkom/Logging.hpp"
#include "gkom/World.hpp"
#include "gkom/Entity.hpp"

namespace gkom {

BoxFactory::BoxFactory(World& world, GeometryManager& geometryManager)
	:	world_(world)
	,	geometryManager_(geometryManager)
	,	logger_(Logging::getLogger("BoxFactory"))
{
	logger_("Initialized");
}

BoxFactory::~BoxFactory() = default;

Entity* BoxFactory::createBox()
{
	auto entity = world_.createEntity();

	if(!geometry_)
	{
		geometry_ = makeBox();
	}

	entity->geometry = *geometry_;
	return entity;
}

std::unique_ptr<Geometry> BoxFactory::makeBox()
{
	logger_("Making new box geometry...");
	const auto vertices = makeVertices();
	const auto geometry =
		geometryManager_.createGeometry(vertices);
	return std::make_unique<Geometry>(geometry);
}

std::vector<Vertex> BoxFactory::makeVertices()
{
	return {
 		{{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
     	{{0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
     	{{0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
     	{{0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
    	{{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},
    	{{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}},

    	{{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f}},
     	{{0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f}},
     	{{0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f}},
     	{{0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f}},
    	{{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f}},
    	{{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f, 1.0f}},

    	{{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
    	{{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
    	{{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
    	{{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}},
    	{{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},
    	{{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}},

     	{{0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}},
     	{{0.5f,  0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}},
     	{{0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}},
     	{{0.5f, -0.5f, -0.5f}, { 1.0f,  0.0f,  0.0f}},
     	{{0.5f, -0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}},
     	{{0.5f,  0.5f,  0.5f}, { 1.0f,  0.0f,  0.0f}},

    	{{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},
     	{{0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},
     	{{0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
     	{{0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
    	{{-0.5f, -0.5f,  0.5f}, { 0.0f, -1.0f,  0.0f}},
    	{{-0.5f, -0.5f, -0.5f}, { 0.0f, -1.0f,  0.0f}},

    	{{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}},
     	{{0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}},
     	{{0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}},
     	{{0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}},
    	{{-0.5f,  0.5f,  0.5f}, { 0.0f,  1.0f,  0.0f}},
    	{{-0.5f,  0.5f, -0.5f}, { 0.0f,  1.0f,  0.0f}}
	};
}

std::vector<glm::vec3> BoxFactory::makePositions()
{
	return {
		// // Back face
		// {-0.5f, -0.5f, -0.5f},
		// { 0.5f, -0.5f, -0.5f},
		// { 0.5f,  0.5f, -0.5f},
		// {-0.5f,  0.5f, -0.5f},

		// Front face
		{-0.5f, -0.5f,  0.5f},
		{ 0.5f, -0.5f,  0.5f},
		{ 0.5f,  0.5f,  0.5f},
		{-0.5f,  0.5f,  0.5f},

		// // Left face
		// {-0.5f,  0.5f,  0.5f},
		// {-0.5f,  0.5f, -0.5f},
		// {-0.5f, -0.5f, -0.5f},
		// {-0.5f, -0.5f,  0.5f},

		// // Right face
		// { 0.5f,  0.5f,  0.5f},
		// { 0.5f,  0.5f, -0.5f},
		// { 0.5f, -0.5f, -0.5f},
		// { 0.5f, -0.5f,  0.5f},

		// // Lower face
		// {-0.5f, -0.5f,  0.5f},
		// {-0.5f, -0.5f, -0.5f},
		// { 0.5f, -0.5f, -0.5f},
		// { 0.5f, -0.5f,  0.5f},

		// // Upper face
		// {-0.5f,  0.5f,  0.5f},
		// {-0.5f,  0.5f, -0.5f},
		// { 0.5f,  0.5f, -0.5f},
		// { 0.5f,  0.5f,  0.5f},
	};
}

std::vector<glm::vec3> BoxFactory::makeNormals()
{
	return {
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f, -1.0f},
		{ 0.0f,  0.0f, -1.0f},

		// { 0.0f,  0.0f,  1.0f},
		// { 0.0f,  0.0f,  1.0f},
		// { 0.0f,  0.0f,  1.0f},
		// { 0.0f,  0.0f,  1.0f},

		// {-1.0f,  0.0f,  0.0f},
		// {-1.0f,  0.0f,  0.0f},
		// {-1.0f,  0.0f,  0.0f},
		// {-1.0f,  0.0f,  0.0f},

		// { 1.0f,  0.0f,  0.0f},
		// { 1.0f,  0.0f,  0.0f},
		// { 1.0f,  0.0f,  0.0f},
		// { 1.0f,  0.0f,  0.0f},

		// { 0.0f, -1.0f,  1.0f},
		// { 0.0f, -1.0f,  1.0f},
		// { 0.0f, -1.0f,  1.0f},
		// { 0.0f, -1.0f,  1.0f},

		// { 0.0f,  1.0f,  0.0f},
		// { 0.0f,  1.0f,  0.0f},
		// { 0.0f,  1.0f,  0.0f},
		// { 0.0f,  1.0f,  0.0f},
	};
}

std::vector<unsigned int> BoxFactory::makeIndices()
{
	return {
		// Back face
		0, 1, 2,
		0, 2, 3,
		// 2, 1, 3,

		// Front face
		// 4, 5, 6,
		// 5, 6, 7,

		// // Left face
		// 8, 9, 10,
		// 10, 11, 8,

		// // Right face
		// 12, 13, 14,
		// 14, 15, 12,

		// // Lower face
		// 16, 17, 18,
		// 18, 19, 16,

		// // Upper face
		// 20, 21, 22,
		// 22, 23, 20
	};
}

} // gkom
