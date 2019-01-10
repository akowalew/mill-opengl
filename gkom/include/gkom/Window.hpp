#pragma once

#include <vector>
#include <functional>

#include "gkom/Context.hpp"
#include "gkom/Object.hpp"

struct GLFWwindow; // Forward declaration

namespace gkom {

class Window
{
public:
	using Handle = GLFWwindow*;

	using KeyPressHandler = std::function<void(int /*code*/, int /*mods*/)>;

	Window();

	~Window();

	Window(Window&& other) noexcept;

	Window& operator=(Window&& other) noexcept;

	void addObject(Object* object);

	void removeObject(Object* object);

	void update();

	void show();

	void hide();

	bool shouldClose() const;

	void setShouldClose(bool shouldClose);

	void setTitle(const char* title);

	void onKeyPress(KeyPressHandler keyPressHandler);

	Handle handle() const noexcept;

private:
	void releaseCallbacks();

	static void keyCallback(Window::Handle handle,
		       		        int key, int scancode,
		       		        int action, int mods);

	static Handle createNative();

	Handle handle_;
	Context context_;
	KeyPressHandler keyPressHandler_;
	std::vector<Object*> objects_;
};

} // gkom
