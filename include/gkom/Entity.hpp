#pragma once

namespace gkom {

// Forward declarations
struct Transform;
struct Color;
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
