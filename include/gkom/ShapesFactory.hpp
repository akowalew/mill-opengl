#pragma once

#include "gkom/BoxFactory.hpp"
#include "gkom/PyramidFactory.hpp"
#include "gkom/ConeFactory.hpp"

namespace gkom {

class Logger;
class Geometry; // Forward declaration
class GraphicsManager; // Forward declaration

class ShapesFactory
{
public:
	ShapesFactory(GraphicsManager& graphicsManager);

	Geometry* createBox();

	Geometry* createPyramid();

	Geometry* createCone(int sides);

	Geometry* createSphere(int segments);

	Geometry* createCylinder(int sides);

private:
	gkom::BoxFactory boxFactory_;
	gkom::PyramidFactory pyramidFactory_;
	gkom::ConeFactory coneFactory_;

	Logger& logger_;
};

} // gkom
