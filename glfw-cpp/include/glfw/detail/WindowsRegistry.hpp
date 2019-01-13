#pragma once

#include <vector>

#include "glfw/Window.hpp"

namespace glfw {
namespace detail {

class WindowsRegistry
{
	using Container = std::vector<Window*>;

public:
	using iterator = Container::iterator;

	static iterator begin()
	{
		return windows_.begin();
	}

	static iterator end()
	{
		return windows_.end();
	}

	static void add(Window* window);

	static void remove(Window* window);

	static Window* at(Window::Handle handle);

	static void replace(Window* oldWindow, Window* newWindow);

private:
	static std::vector<Window*> windows_;
};

} // detail
} // glfw
