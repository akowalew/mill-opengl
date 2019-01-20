#pragma once

#include <vector>

#include <glm/vec4.hpp>

#include "gkom/Camera.hpp"

namespace gkom {

//! Forward declarations
class Logger;
class Entity;

using Color = glm::vec4;

class Renderer
{
public:
	Renderer();

	void render(const std::vector<Entity*>& entities);

	void surfaceChanged(int width, int height);

	void setCamera(Camera* camera);

	Camera* camera();

	const Camera* camera() const;

	void setBackgroundColor(const glm::vec4& bgColor);

	const Color& backgroundColor() const;

private:
	Color bgColor_ {0.0f, 0.0f, 0.0f, 1.0f};
	Camera defaultCamera_;
	Camera* camera_ {&defaultCamera_};
	Logger& logger_;
};

} // gkom
