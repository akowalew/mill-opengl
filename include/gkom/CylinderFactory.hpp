#pragma once

#include <unordered_map>

namespace gkom {
namespace meshes {

//! Forward declarations
class GraphicsManager;
class Mesh;

class CylinderFactory
{
public:
	CylinderFactory(GraphicsManager& graphicsManager);

	Mesh* createCylinder(int sides);

private:
	GraphicsManager& graphicsManager_;
	std::unordered_map<int /*sides*/, Mesh*> cylinders_;
};

} // meshes
} // gkom
