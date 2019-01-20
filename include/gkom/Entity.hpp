#pragma once

#include "gkom/Transform.hpp"

namespace gkom {

// Forward declarations
class Mesh;
class Material;

class Entity
{
public:
	Transform transform;

	Mesh* mesh {nullptr};
	Material* material {nullptr};
};

} // gkom
