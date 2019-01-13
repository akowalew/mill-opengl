#include "glfw/Application.hpp"

#include <cassert>
#include <cstdio>

#include <GLFW/glfw3.h>

#include "glfw/detail/WindowsRegistry.hpp"

namespace glfw {

Application::Application()
{
	puts("[GLFW][Application] Initializing...");
	if(glfwInit() != GL_TRUE)
	{
		throw std::runtime_error("Could not initialize application");
	}
}

Application::~Application()
{
	glfwTerminate();
	puts("[GLFW][Application] Terminated");
}

int Application::exec()
{
	puts("[GLFW][Application] Running...");
	while(true)
	{
		glfwPollEvents();

		bool shouldClose = true;
		std::for_each(detail::WindowsRegistry::begin(),
			          detail::WindowsRegistry::end(),
			          [&shouldClose](Window* window)
			          {
				          assert(window);
				          if(window->shouldClose())
				          {
					          return;
				          }

				          shouldClose = false;
				          window->update();
			          });

		if(shouldClose)
		{
			break;
		}
	}

	puts("[GLFW][Application] Finished");
	return 0;
}

} // glfw
