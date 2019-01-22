#pragma once

#include <glm/vec3.hpp>

namespace gkom {

//! Forward declarations
class World;
class Entity;
class Logger;

class LightFactory
{
public:
	explicit LightFactory(World& world);

	~LightFactory();

	// TODO: Transform, because omni light have maybe only position,
	//	but directed light or linear light not

	// TODO: There should be a LightBuilder
	//  which could have methods like:
	//    withColor(col), withPosition(pos), attachedTo(node)

	// TODO: question: do we really need Scene here?

	Entity* createLight(const glm::vec3& position,
					   	const glm::vec3& color);

private:
	World& world_;
	Logger& logger_;
};

} // gkom
