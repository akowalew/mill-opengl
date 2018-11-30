#include "gl/glew.hpp"
#include "glfw/Window.hpp"

#include <cassert>
#include <cstdio>
#include <algorithm>
#include <stdexcept>
#include <vector>

#include <GLFW/glfw3.h>

namespace glfw {
namespace {

std::vector<Window*> gWindows;

Window::Handle createNative(int width, int height,
                            const char* title,
                            const Window::Hints& hints,
                            GLFWmonitor* monitor,
                            GLFWwindow* share);

void registerWindow(Window* window);

void unregisterWindow(Window* window);

Window* getWindow(Window::Handle handle);

void replaceWindow(Window* oldWindow, Window* newWindow);

} //

Window::Window(int width, int height,
			   const char* title,
	           const Hints& hints,
	           GLFWmonitor* monitor,
	           GLFWwindow* share)
	:	handle(createNative(width, height, title, hints, monitor, share))
{
	assert(handle);

	puts("[GLFW][Window] Initializing...");
	activate();
	glewExperimental = GL_TRUE;
	glew::init();

	registerWindow(this);
}

Window::~Window()
{
	if(handle)
	{
		releaseCallbacks();
		unregisterWindow(this);

		glfwDestroyWindow(handle);
		puts("[GLFW][Window] Destroyed");
	}
}

Window::Window(Window&& other) noexcept
{
	*this = std::move(other);
}

Window&
Window::operator=(Window &&other) noexcept
{
	replaceWindow(&other, this);

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

void
Window::onKeyPress(KeyPressHandler keyPressHandler)
{
	if(!keyPressHandler)
	{
		glfwSetKeyCallback(handle, nullptr);
		keyPressHandler_ = nullptr;

		puts("[GLFW][Window] Key press callback unregistered");

		return;
	}

	puts("[GLFW][Window] Registering key press callback...");
	keyPressHandler_ = std::move(keyPressHandler);
	glfwSetKeyCallback(handle, keyCallback);
}

void Window::releaseCallbacks()
{
	onKeyPress(nullptr);

	puts("[GLFW][Window] Callbacks released");
}

void Window::keyCallback(Window::Handle handle,
	             		 int key, int /*scancode*/,
	             		 int action, int mods)
{
	// printf("[GLFW][Window] Key callback: %p, %d, %d, %d\n",
           // handle, key, action, mods);

	auto window = getWindow(handle);
	assert(window);

	if(action == GLFW_PRESS)
	{
		assert(window->keyPressHandler_);
		window->keyPressHandler_(key, mods);
	}
}

namespace {

Window::Handle createNative(int width, int height,
	         			    const char* title,
	         			    const Window::Hints& hints,
	         			    GLFWmonitor* monitor,
	         			    GLFWwindow* share)
{
	puts("[GLFW][Window] Applying hints...");
	for(const auto [hint, value]: hints)
	{
		glfwWindowHint(hint, value);
	}

	puts("[GLFW][Window] Creating...");
	auto handle = glfwCreateWindow(width, height, title, monitor, share);
	if(!handle)
	{
		throw std::runtime_error("Could not create GLFWwindow");
	}

	return handle;
}

void registerWindow(Window* window)
{
	puts("[GLFW][Window] Registering window...");

	const auto gWindowsEnd = gWindows.end();
	const auto pos = std::find(gWindows.begin(),
		                       gWindowsEnd,
		                       window);

	// Preconditions
	assert(pos == gWindowsEnd);

	gWindows.insert(gWindowsEnd, window);
}

void unregisterWindow(Window* window)
{
	const auto gWindowsEnd = gWindows.end();
	const auto pos = std::find(gWindows.begin(),
		                       gWindows.end(),
		                       window);

	// Preconditions
	assert(pos != gWindowsEnd);

	gWindows.erase(pos);

	puts("[GLFW][Window] Window unregistered");
}

Window* getWindow(Window::Handle handle)
{
	// printf("[GLFW][Window] Getting window with handle %p...\n", handle);

	const auto predicate =
		[handle] (auto window) { return *window == handle; };

	const auto gWindowsEnd = gWindows.end();
	const auto pos = std::find_if(gWindows.begin(),
					    	      gWindowsEnd,
					              predicate);
	assert(pos != gWindowsEnd);
	return *pos;
}

void replaceWindow(Window* oldWindow, Window* newWindow)
{
	puts("[GLFW][Window] Replacing window...");

	const auto gWindowsEnd = gWindows.end();
	const auto pos = std::find(gWindows.begin(),
							   gWindowsEnd,
							   oldWindow);

	assert(pos != gWindowsEnd);
	*pos = newWindow;
}

} //
} // glfw


