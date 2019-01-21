#pragma once

#include "gkom/BoxFactory.hpp"
#include "gkom/PyramidFactory.hpp"
#include "gkom/ConeFactory.hpp"
#include "gkom/PrismFactory.hpp"

namespace gkom {

class Logger;
class Mesh; // Forward declaration

class ShapesFactory
{
public:
	ShapesFactory();

	// TODO: Add ShapeBuilder to make easy calls like:
	//  builder.withNormals(true), builder.withBitangents(true) etc

	Mesh* createBox();

	Mesh* createBoxWithNormals();

	Mesh* createPyramid();

	Mesh* createCone(int sides);

	Mesh* createPrism(int sides);

private:
	gkom::BoxFactory boxFactory_;
	// gkom::PyramidFactory pyramidFactory_;
	// gkom::ConeFactory coneFactory_;
	// gkom::PrismFactory prismFactory_;

	Logger& logger_;
};

} // gkom
