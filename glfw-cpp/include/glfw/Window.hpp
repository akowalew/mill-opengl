#pragma once

#include <functional>
#include <initializer_list>
#include <utility>

#include <GLFW/glfw3.h>

namespace glfw {

class Window
{
public:
	using Handle = GLFWwindow*;

	using Hints =
		std::initializer_list<std::pair<int /*hint*/, int /*value*/>>;

	using KeyPressHandler =
		std::function<void(int /*code*/, int /*mods*/)>;

	Window(int width, int height, const char* title,
		   const Hints& hints = Hints{},
		   GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

	~Window();

	Window(Window&& other) noexcept;

	Window& operator=(Window&& other) noexcept;

	void shouldClose(bool value);

	bool shouldClose() const;

	void display();

	void activate();

	void onKeyPress(KeyPressHandler keyPressHandler);

	operator Handle() const noexcept { return handle; }

private:
	void releaseCallbacks();

	static void keyCallback(Window::Handle handle,
		       		        int key, int scancode,
		       		        int action, int mods);

	Handle handle = nullptr;
	KeyPressHandler keyPressHandler_;
};

} // glfw
