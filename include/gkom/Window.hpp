#pragma once

#include <deque>
#include <chrono>

#include "gkom/Size.hpp"
#include "gkom/Event.hpp"

struct GLFWwindow; // Forward declaration

namespace gkom {

//! Forward declarations
class Logger;

class Window
{
public:
	using Handle = GLFWwindow*;

	Window();

	~Window();

	Window(Window&& other) noexcept;

	Window& operator=(Window&& other) noexcept;

	void activate();

	void deactivate();

	void show();

	void hide();

	bool shouldClose() const;

	void update();

	bool pollEvent(Event& event);

	bool waitEvent(Event& event);

	bool waitEventFor(std::chrono::duration<double> timeout, Event& e);

	void setShouldClose(bool shouldClose);

	void setSize(Size size);

	void setTitle(const char* title);

	Handle handle() const noexcept;

	Size size() const;

private:
	void setupCallbacks();

	void setupContext();

	void releaseCallbacks();

	bool popEvent(Event& event);

	static void keyCallback(Window::Handle handle,
		       		        int key, int scancode,
		       		        int action, int mods);

	static void sizeCallback(Window::Handle handle,
							 int width, int height);

	static Handle createNative();

	Handle handle_;
	std::deque<Event> events_;
	Logger& logger_;
};

} // gkom
