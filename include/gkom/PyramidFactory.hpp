#pragma once

#include <memory>
#include <vector>

namespace gkom {

//! Forward declarations
class GeometryManager;
class World;
class Geometry;
class Logger;
class Entity;
class Vertex;

class PyramidFactory
{
public:
	PyramidFactory(World& world, GeometryManager& geometryManager);

	~PyramidFactory();

	Entity* createPyramid();

private:
	std::unique_ptr<Geometry> makePyramid();

	std::vector<Vertex> makeVertices();

	World& world_;
	GeometryManager& geometryManager_;
	Logger& logger_;
	std::unique_ptr<Geometry> pyramid_;
};

} // gkom
