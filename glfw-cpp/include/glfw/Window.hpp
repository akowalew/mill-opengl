#pragma once

#include <initializer_list>
#include <utility>

#include <GLFW/glfw3.h>

namespace glfw {

class Window
{
public:
	using Handle = GLFWwindow*;

	using Hints =
		std::initializer_list<
			std::pair<int /*hint*/, int /*value*/>>;

	Window(int width, int height,
		   const char* title,
		   const Hints& hints = Hints{},
		   GLFWmonitor* monitor = nullptr,
		   GLFWwindow* share = nullptr);

	~Window();

	Window(Window&& other) noexcept;

	Window& operator=(Window&& other) noexcept;

	void shouldClose(bool value);

	bool shouldClose() const;

	void display();

	void activate();

	operator Handle() const noexcept { return handle; }

private:
	static Handle createNative(int width, int height,
		                       const char* title,
		                       const Hints& hints,
		                       GLFWmonitor* monitor,
		                       GLFWwindow* share);

	Handle handle = nullptr;
};

} // glfw
