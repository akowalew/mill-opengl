#pragma once

#include "glfw/Size.hpp"

namespace glfw {

class Renderer
{
public:
	virtual void onSurfaceCreated() = 0;

	virtual void onSurfaceChanged(Size size) = 0;

	virtual void onDraw() = 0;
};

} // glfw
