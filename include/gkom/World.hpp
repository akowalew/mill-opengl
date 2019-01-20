#pragma once

#include <vector>
#include <memory>

namespace gkom {

//! Forward declarations
class Entity;
class Logger;

class World
{
public:
	World();

	~World();

	Entity* createEntity();

	void clear();

private:
	std::vector<std::unique_ptr<Entity>> entities;
	Logger& logger_;
};

} // gkom
