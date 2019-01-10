#include "gkom/Application.hpp"

#include <cassert>
#include <cstdio>

#include <GLFW/glfw3.h>

#include "gkom/detail/WindowsRegistry.hpp"

namespace gkom {

Application::Application()
{
	puts("[GKOM][Application] Initializing...");
	if(glfwInit() != GL_TRUE)
	{
		throw std::runtime_error("Could not initialize application");
	}
}

Application::~Application()
{
	glfwTerminate();
	puts("[GKOM][Application] Terminated");
}

int Application::exec()
{
	puts("[GKOM][Application] Running...");
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

	puts("[GKOM][Application] Finished");
	return 0;
}

} // gkom
