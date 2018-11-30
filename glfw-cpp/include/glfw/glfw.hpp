#pragma once

#include <GLFW/glfw3.h>

#include "glfw/Window.hpp"

namespace glfw {

void
init();

void
terminate();

inline void
pollEvents()
{
	glfwPollEvents();
}

} // glfw
