#pragma once

#include "gkom/BoxFactory.hpp"
#include "gkom/PyramidFactory.hpp"
#include "gkom/ConeFactory.hpp"
#include "gkom/PrismFactory.hpp"

namespace gkom {

class GeometryManager;
class Logger;
struct Geometry; // Forward declaration
class World; // Forward declaration

class ShapesFactory
{
public:
	ShapesFactory(World& world, GeometryManager& geometryManager);

	// TODO: Add ShapeBuilder to make easy calls like:
	//  builder.withNormals(true), builder.withBitangents(true) etc

	Entity* createBox();

	Entity* createPyramid();

	Entity* createCone(int sides);

	Entity* createPrism(int sides);

private:
	gkom::BoxFactory boxFactory_;
	gkom::PyramidFactory pyramidFactory_;
	gkom::ConeFactory coneFactory_;
	gkom::PrismFactory prismFactory_;

	Logger& logger_;
};

} // gkom
