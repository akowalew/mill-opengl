#pragma once

#include <vector>

#include <glm/vec3.hpp>

namespace gkom {

//! Forward declarations
class TransformManager;
class ColorFactory;
class World;
class Scene;
class Entity;
class Logger;

class LightManager
{
public:
	LightManager(World& world,
				 TransformManager& transformManager,
				 ColorFactory& colorFactory);

	~LightManager();

	// TODO: Maybe throw away TransformManager and ColorManager
	//  and let the caller sent arleady created transforms, colors?

	// TODO: Transform, because omni light have maybe only position,
	//	but directed light or linear light not

	// TODO: There should be a LightBuilder
	//  which could have methods like:
	//    withColor(col), withPosition(pos), attachedTo(node)

	// TODO: question: do we really need Scene here?

	Entity* createLight(const glm::vec3& position,
					   	const glm::vec3& color);

	const std::vector<Entity*>& lights() const;

private:
	std::vector<Entity*> lights_;

	World& world_;
	TransformManager& transformManager_;
	ColorFactory& colorFactory_;
	Logger& logger_;
};

} // gkom
