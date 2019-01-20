#pragma once

#include "gkom/BoxFactory.hpp"

namespace gkom {

class Logger;
class Mesh; // Forward declaration
class GraphicsManager; // Forward declaration

class ShapesFactory
{
public:
	ShapesFactory(GraphicsManager& graphicsManager);

	Mesh* createBox();

	Mesh* createPyramid();

	Mesh* createCone(int sides);

	Mesh* createSphere(int segments);

	Mesh* createCylinder(int sides);

private:
	gkom::BoxFactory boxFactory_;

	Logger& logger_;
};

} // gkom
