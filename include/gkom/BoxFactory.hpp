#pragma once

#include <memory>

namespace gkom {

//! Forward declarations
class Geometry;
class GraphicsManager;
class Logger;

class BoxFactory
{
public:
	BoxFactory(GraphicsManager& graphicsManager);

	~BoxFactory();

	Geometry* createBox();

private:
	std::unique_ptr<Geometry> makeBox();

	GraphicsManager& graphicsManager_;
	std::unique_ptr<Geometry> box_;
	Logger& logger_;
};

} // gkom
