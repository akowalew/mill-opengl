#pragma once

#include <vector>
#include <functional>

#include "glfw/Context.hpp"
#include "glfw/Renderer.hpp"

struct GLFWwindow; // Forward declaration

namespace glfw {

class Window
{
public:
	using Handle = GLFWwindow*;

	using KeyPressHandler = std::function<void(int /*code*/, int /*mods*/)>;

	Window();

	~Window();

	Window(Window&& other) noexcept;

	Window& operator=(Window&& other) noexcept;

	void update();

	void show();

	void hide();

	bool shouldClose() const;

	void setShouldClose(bool shouldClose);

	void setTitle(const char* title);

	void onKeyPress(KeyPressHandler keyPressHandler);

	void setRenderer(Renderer* renderer);

	Size size() const;

	Handle handle() const noexcept;

private:
	void listenSizeCallback();

	void releaseCallbacks();

	static void keyCallback(Window::Handle handle,
		       		        int key, int scancode,
		       		        int action, int mods);

	static void sizeCallback(Window::Handle handle,
							 int width, int height);

	static Handle createNative();

	Handle handle_;
	Context context_;
	KeyPressHandler keyPressHandler_;
	Renderer* renderer_ {nullptr};
};

} // glfw
