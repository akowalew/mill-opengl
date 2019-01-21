#pragma once

#include "gkom/Camera.hpp"
#include "gkom/Color.hpp"

namespace gkom {

//! Forward declarations
class Scene;
class Logger;
class Entity;
class SceneNode;
class Transform;

class Renderer
{
public:
	Renderer();

	void render();

	void surfaceChanged(int width, int height);

	void setScene(Scene* scene);

	Scene* scene();

	void setCamera(Camera* camera);

	Camera* camera();

	// TODO: Maybe light should be provided by scene?
	// TODO: Or maybe light should be provided by LightManager
	// TODO: Or even better maybe light should be sent through some event?

	void setLight(Entity* light);

	Entity* light();

	void setBackgroundColor(const Color& bgColor);

	const Color& backgroundColor() const;

private:
	void render(SceneNode* node, const Transform& transform);

	void render(Entity* entity, const Transform& transform);

	Camera defaultCamera_;
	Color bgColor_;
	Camera* camera_ {&defaultCamera_};
	Scene* scene_ {nullptr};
	Entity* light_ {nullptr};
	Logger& logger_;
};

} // gkom
