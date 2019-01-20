#pragma once

#include "gkom/BoxFactory.hpp"

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

	Logger& logger_;
};

} // gkom
