#pragma once

namespace gkom {
namespace meshes {

//! Forward declarations
class GraphicsManager;
class Mesh;

class PyramidFactory
{
public:
	PyramidFactory(GraphicsManager& graphicsManager);

	Mesh* createPyramid();

private:
	GraphicsManager& graphicsManager_;
	Mesh* pyramid_ {nullptr};
};

} // meshes
} // gkom
