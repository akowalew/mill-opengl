#pragma once

namespace gkom {

// Forward declarations
class Transform;
class Color;
class Geometry;
class Material;

class Entity
{
public:
	Transform* transform {nullptr};
	Color* color {nullptr};
	Geometry* geometry {nullptr};
	Material* material {nullptr};
};

} // gkom
