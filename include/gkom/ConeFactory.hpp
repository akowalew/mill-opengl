#pragma once

#include <memory>
#include <unordered_map>

#include "gkom/Geometry.hpp"

namespace gkom {

//! Forward declarations
class GeometryManager;
class World;
struct Geometry;
class Logger;
class Entity;
struct Vertex;

class ConeFactory
{
public:
	ConeFactory(World& world, GeometryManager& geometryManager);

	~ConeFactory();

	Entity* createCone(int sides);

private:
	Geometry makeCone(int sides);

	std::vector<Vertex> makeVertices(int sides);

	World& world_;
	GeometryManager& geometryManager_;
	Logger& logger_;
};

} // gkom
