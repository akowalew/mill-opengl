#pragma once

#include <vector>
#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace gkom {

//! Forward declarations
class Logger;
class GeometryManager;
class Geometry;
class World;
class Entity;
class Vertex;

class BoxFactory
{
public:
	BoxFactory(World& world, GeometryManager& geometryManager);

	~BoxFactory();

	// TODO: Add builder:
	// withNormals(true), statical(true), dynamical(false) etc

	Entity* createBox();

private:
	std::unique_ptr<Geometry> makeBox();

	std::vector<Vertex> makeVertices();

	std::vector<glm::vec3> makePositions();

	std::vector<glm::vec3> makeNormals();

	std::vector<glm::vec2> makeTexcoords();

	std::vector<unsigned int> makeIndices();

	World& world_;
	GeometryManager& geometryManager_;
	Logger& logger_;
	std::unique_ptr<Geometry> geometry_;
};

} // gkom
