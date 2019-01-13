#pragma once

struct GLFWwindow; // Forward declaration

namespace glfw {

class Context
{
public:
	using Handle = GLFWwindow*;

	explicit Context(Handle handle);

	~Context();

	Context(Context&& other) noexcept;

	Context& operator=(Context&& other) noexcept;

	void activate();

	void deactivate();

	void swapBuffers();

private:
	Handle handle_;
};

} // glfw
