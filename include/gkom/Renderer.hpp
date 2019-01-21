#pragma once

#include <vector>

#include <glm/vec4.hpp>

#include "gkom/Camera.hpp"

namespace gkom {

//! Forward declarations
class Scene;
class Logger;
class Entity;
class SceneNode;

using Color = glm::vec4;

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

	const Camera* camera() const;

	void setBackgroundColor(const glm::vec4& bgColor);

	const Color& backgroundColor() const;

private:
	void render(SceneNode* node);

	void render(Entity* entity);

	Color bgColor_ {0.0f, 0.0f, 0.0f, 1.0f};
	Camera defaultCamera_;
	Camera* camera_ {&defaultCamera_};
	Scene* scene_ {nullptr};
	Logger& logger_;
};

} // gkom
