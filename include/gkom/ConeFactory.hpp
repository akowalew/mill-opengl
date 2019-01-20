#pragma once

#include <unordered_map>

namespace gkom {
namespace meshes {

//! Forward declarations
class GraphicsManager;
class Mesh;

class ConeFactory
{
public:
	ConeFactory(GraphicsManager& graphicsManager);

	Mesh* createCone(int sides);

private:
	GraphicsManager& graphicsManager_;
	std::unordered_map<int /*sides*/, Mesh*> cones_;
};

} // meshes
} // gkom
