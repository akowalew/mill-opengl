#include "glfw/glfw.hpp"

#include <cstdio>
#include <stdexcept>

namespace glfw {

namespace {

bool initialized = false;

void doTerminate()
{
	puts("[GLFW] Terminating...");
	glfwTerminate();
}

}

void
init()
{
	if(!initialized)
	{
		std::atexit(doTerminate);

		puts("[GLFW] Initializing...");
		if(glfwInit() != GL_TRUE)
		{
			throw std::runtime_error("Could not initialize GLFW");
		}
	}
}

void
terminate()
{
	doTerminate();
}

} // glfw
