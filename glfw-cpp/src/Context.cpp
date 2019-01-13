#include "glfw/Context.hpp"

#include <cassert>
#include <cstdio>
#include <stdexcept>

#include "gl/gl.hpp"
#include <GLFW/glfw3.h>

namespace glfw {

Context::Context(Handle handle)
	:	handle_(handle)
{
	assert(handle_);

	puts("[GLFW][Context] Initializing...");
	activate();
	gl::init();
}

Context::~Context()
{
	if(handle_ != nullptr)
	{
		puts("[GLFW][Context] Destroyed");
	}
}

Context::Context(Context&& other) noexcept
{
	*this = std::move(other);
}

Context&
Context::operator=(Context &&other) noexcept
{
	if(&other != this)
	{
		handle_ = other.handle_;
		other.handle_ = nullptr;
	}

	return *this;
}

void Context::activate()
{
	glfwMakeContextCurrent(handle_);
}

void Context::deactivate()
{
	glfwMakeContextCurrent(nullptr);
}

void Context::swapBuffers()
{
	glfwSwapBuffers(handle_);
}

} // glfw
