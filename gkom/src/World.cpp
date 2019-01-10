#include "gkom/World.hpp"

#include <cassert>
#include <cstdio>
#include <algorithm>

namespace gkom {

void World::addShape(Shape* shape)
{
	assert(shape);
	assert(std::find(shapes_.begin(), shapes_.end(), shape) == shapes_.end());
	printf("[GKOM][World] Adding shape: %p...\n", shape);
	shapes_.push_back(shape);
}

void World::removeShape(Shape* shape)
{
	assert(shape);
	printf("[GKOM][World] Removing shape: %p...\n", shape);
	const auto pos = std::remove(shapes_.begin(), shapes_.end(), shape);
	shapes_.erase(pos, shapes_.end());
}

const std::vector<Shape*> World::shapes() const
{
	return shapes_;
}

} // gkom
