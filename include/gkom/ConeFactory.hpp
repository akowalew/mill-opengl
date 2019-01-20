#pragma once

#include <memory>
#include <unordered_map>

#include "gkom/Geometry.hpp"

namespace gkom {

//! Forward declarations
class GraphicsManager;
class Geometry;
class Logger;

class ConeFactory
{
public:
	ConeFactory(GraphicsManager& graphicsManager);

	~ConeFactory();

	Geometry* createCone(int sides);

	Geometry* findCone(int sides);

private:
	Geometry makeCone(int sides);

	GraphicsManager& graphicsManager_;
	Logger& logger_;
	std::unordered_map<int /*sides*/, Geometry> cones_;
};

} // gkom
