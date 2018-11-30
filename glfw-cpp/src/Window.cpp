#include "gl/glew.hpp"
#include "glfw/Window.hpp"

#include <cassert>
#include <cstdio>
#include <algorithm>
#include <stdexcept>

#include <GLFW/glfw3.h>

namespace glfw {

Window::Window(int width, int height,
	           const char* title,
	           const Hints& hints,
	           GLFWmonitor* monitor,
	           GLFWwindow* share)
	:	handle(createNative(width, height, title, hints, monitor, share))
{
	// Preconditions
	assert(handle);

	activate();
	glewExperimental = GL_TRUE;
	glew::init();
}

Window::~Window()
{
	if(handle)
	{
		puts("[GLFW] Destroying window...");
		glfwDestroyWindow(handle);
	}
}

Window::Window(Window&& other) noexcept
{
	*this = std::move(other);
}

Window&
Window::operator=(Window &&other) noexcept
{
	handle = other.handle;
	other.handle = nullptr;
	return *this;
}

void
Window::display()
{
	glfwSwapBuffers(handle);
}

bool
Window::shouldClose() const
{
	return glfwWindowShouldClose(handle);
}

void
Window::shouldClose(bool value)
{
	glfwSetWindowShouldClose(handle, value);
}

void
Window::activate()
{
	glfwMakeContextCurrent(handle);
}

Window::Handle
Window::createNative(int width, int height,
	                 const char* title,
	                 const Hints& hints,
	                 GLFWmonitor* monitor,
	                 GLFWwindow* share)
{
	for(const auto [hint, value]: hints)
	{
		glfwWindowHint(hint, value);
	}

	puts("[GLFW] Creating window...");
	auto handle = glfwCreateWindow(width, height, title, monitor, share);
	if(!handle)
	{
		throw std::runtime_error("Could not create GLFWwindow");
	}

	return handle;
}

} // glfw
