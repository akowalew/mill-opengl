#pragma once

#include <memory>
#include <unordered_map>

#include "gkom/Geometry.hpp"

namespace gkom {

//! Forward declarations
class GeometryManager;
class World;
class Geometry;
class Logger;
class Entity;
class Vertex;

class PrismFactory
{
public:
	PrismFactory(World& world, GeometryManager& geometryManager);

	~PrismFactory();

	Entity* createPrism(int sides);

private:
	Geometry makePrism(int sides);

	std::vector<Vertex> makeVertices(int sides);

	World& world_;
	GeometryManager& geometryManager_;
	Logger& logger_;
};

} // gkom
