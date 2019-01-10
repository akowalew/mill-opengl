#include "gkom/detail/WindowsRegistry.hpp"

#include <cassert>
#include <cstdio>

namespace gkom {
namespace detail {

WindowsRegistry::Container WindowsRegistry::windows_ {};

void WindowsRegistry::add(Window* window)
{
	assert(window);
	printf("[GKOM][Window] Registering window %p...\n", window);
	const auto windowsEnd = windows_.end();
	const auto pos = std::find(windows_.begin(),
		                       windowsEnd,
		                       window);

	// Preconditions
	assert(pos == windowsEnd);
	windows_.insert(windowsEnd, window);
}

void WindowsRegistry::remove(Window* window)
{
	assert(window);
	const auto windowsEnd = windows_.end();
	const auto pos = std::find(windows_.begin(),
		                       windows_.end(),
		                       window);

	// Preconditions
	assert(pos != windowsEnd);
	windows_.erase(pos);
	printf("[GKOM][Window] Window %p unregistered\n", window);
}

Window* WindowsRegistry::at(Window::Handle handle)
{
	assert(handle);
	printf("[GKOM][Window] Getting window with handle %p...\n", handle);
	const auto predicate = [handle] (auto window)
	                       {
		                       return window->handle() == handle;
		                   };

	const auto windowsEnd = windows_.end();
	const auto pos = std::find_if(windows_.begin(),
					    	      windowsEnd,
					              predicate);
	assert(pos != windowsEnd);
	auto window = *pos;
	assert(window);
	return window;
}

void WindowsRegistry::replace(Window* oldWindow, Window* newWindow)
{
	assert(oldWindow);
	assert(newWindow);
	printf("[GKOM][Window] Replacing window %p with %p...\n",
		   oldWindow, newWindow);

	const auto windowsEnd = windows_.end();
	const auto pos = std::find(windows_.begin(),
							   windowsEnd,
							   oldWindow);

	assert(pos != windowsEnd);
	*pos = newWindow;
}

} // detail
} // gkom
