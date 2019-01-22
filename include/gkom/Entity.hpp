#pragma once

#include <optional>

#include "gkom/Transform.hpp"
#include "gkom/Geometry.hpp"
#include "gkom/Material.hpp"
#include "gkom/Light.hpp"

namespace gkom {

class Entity
{
public:
	// Transform component is something, which could be managed standalone
	// geometry, material, are components, which must be provided by some
	//  sort of manager

	std::optional<Transform> transform;
	std::optional<Geometry> geometry;
	std::optional<Material> material;
	std::optional<Light> light;

	// TODO: At the moment there are pointer, but maybe id's
};

} // gkom
