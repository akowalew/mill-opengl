#pragma once

#include <memory>

namespace gkom {

//! Forward declarations
class Mesh;
class GraphicsManager;
class Logger;

class BoxFactory
{
public:
	BoxFactory(GraphicsManager& graphicsManager);

	~BoxFactory();

	Mesh* createBox();

private:
	std::unique_ptr<Mesh> makeBox();

	GraphicsManager& graphicsManager_;
	std::unique_ptr<Mesh> box_;
	Logger& logger_;
};

} // gkom
