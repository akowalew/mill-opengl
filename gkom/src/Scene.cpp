#include "gkom/Scene.hpp"

#include "gl/gl.hpp"

namespace gkom {

Scene::Scene()
{
	gl::enableCapability(GL_DEPTH_TEST);
}

void Scene::render()
{
	gl::setClearColor(backgroundColor_);
	gl::clearBuffers(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// for each shape in world
	//  shape.render() ???
}

void Scene::setActiveWorld(World* world)
{
	assert(world);
	world_ = world;
}

void Scene::setActiveCamera(Camera* camera)
{
	assert(camera);
	camera_ = camera;
}

const glm::vec4& Scene::backgroundColor() const
{
	return backgroundColor_;
}

void Scene::setBackgroundColor(const glm::vec4& backgroundColor)
{
	backgroundColor_ = backgroundColor;
}

} // gkom
