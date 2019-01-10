#pragma once

#include "glm/vec4.hpp"

#include "gkom/World.hpp"
#include "gkom/Camera.hpp"
#include "gkom/Object.hpp"

namespace gkom {

class Scene
	:	public Object
{
public:
	Scene();

	void render() override;

	void setActiveWorld(World* world);

	void setActiveCamera(Camera* camera);

	const glm::vec4& backgroundColor() const;

	void setBackgroundColor(const glm::vec4& backgroundColor);

private:
	glm::vec4 backgroundColor_ {0.0f, 0.0f, 0.0f, 1.0f};
	World* world_ {nullptr};
	Camera* camera_ {nullptr};
};

} // gkom
