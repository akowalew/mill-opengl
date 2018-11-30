/**
 * main.cpp
 * @brief Entry point of the application
 */

#include <cstdio>
#include <stdexcept>
#include <array>

#include "gl/gl.hpp"
#include "glfw/glfw.hpp"

#include "Triangle.hpp"
#include "Rectangle.hpp"

constexpr auto WindowWidth = 800;
constexpr auto WindowHeight = 600;
constexpr auto WindowTitle = "ZW1-Mlyn";

// #define BackgroundColor 0.1f, 0.0f, 0.0f, 1.0f
constexpr std::array<GLfloat, 4> BackgroundColor =
	{{0.1f, 0.0f, 0.0f, 1.0f}};

void GLAPIENTRY
messageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam)
{
	fprintf( stderr, "[GL] %s type = 0x%x, severity = 0x%x, message = %s\n",
	       ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
	        type, severity, message );
	assert(type != GL_DEBUG_TYPE_ERROR);
}


int main(int /*argc*/, char** /*argv*/)
{
	glfw::init();

	try
	{
		const auto windowHints = glfw::Window::Hints{
			{GLFW_SAMPLES, 4},
            {GLFW_CONTEXT_VERSION_MAJOR, 3},
            {GLFW_CONTEXT_VERSION_MINOR, 3},
            {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
		    {GLFW_RESIZABLE, GL_FALSE}};
		auto window = glfw::Window{WindowWidth, WindowHeight,
			                       WindowTitle, windowHints};

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(messageCallback, 0);

		auto triangle = Triangle{};
		auto rectangle = Rectangle{};

		puts("[Application] Started");
		while(!window.shouldClose())
		{
			glfw::pollEvents();

			window.activate();
			std::apply(glClearColor, BackgroundColor);
			glClear(GL_COLOR_BUFFER_BIT);

			triangle.draw();
			rectangle.draw();

			window.display();
		}
	}
	catch(std::exception& ex)
	{
		printf("Exception occured: '%s'\n", ex.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
