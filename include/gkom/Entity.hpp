#pragma once

namespace gkom {

// Forward declarations
class Transform;
class Geometry;
class Material;

class Entity
{
public:
	Transform* transform {nullptr};
	Geometry* geometry {nullptr};
	Material* material {nullptr};
};

} // gkom
