#pragma once

#pragma once

#include <unordered_map>

namespace gkom {
namespace meshes {

//! Forward declarations
class GraphicsManager;
class Mesh;

class SphereFactory
{
public:
	SphereFactory(GraphicsManager& graphicsManager);

	Mesh* createSphere(int segments);

private:
	GraphicsManager& graphicsManager_;
	std::unordered_map<int /*segments*/, Mesh*> spheres_;
};

} // meshes
} // gkom
