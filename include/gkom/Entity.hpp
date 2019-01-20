#pragma once

#include "gkom/Transform.hpp"

namespace gkom {

// Forward declarations
class Geometry;
class Material;

class Entity
{
public:
	Transform transform;

	Geometry* geometry {nullptr};
	Material* material {nullptr};
};

} // gkom
