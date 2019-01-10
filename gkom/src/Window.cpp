#include "gkom/Window.hpp"

#include <algorithm>
#include <cassert>

#include <GLFW/glfw3.h>

#include "gkom/detail/WindowsRegistry.hpp"

namespace gkom {

Window::Window()
	:	handle_(createNative())
	,	context_(handle_)
{
	assert(handle_);
	detail::WindowsRegistry::add(this);
	puts("[GKOM][Window] Initialized");
}

Window::~Window()
{
	if(handle_ != nullptr)
	{
		releaseCallbacks();
		detail::WindowsRegistry::remove(this);

		glfwDestroyWindow(handle_);
		puts("[GKOM][Window] Destroyed");
	}
}

Window::Window(Window&& other) noexcept
	:	handle_(std::move(other.handle_))
	,	context_(std::move(other.handle_))
{
	detail::WindowsRegistry::replace(&other, this);

	other.handle_ = nullptr;
}

Window& Window::operator=(Window &&other) noexcept
{
	detail::WindowsRegistry::replace(&other, this);

	if(&other != this)
	{
		handle_ = std::move(other.handle_);
		context_ = std::move(other.context_);
		other.handle_ = nullptr;
	}

	return *this;
}

void Window::addObject(Object* object)
{
	assert(object);
	assert(std::find(objects_.begin(), objects_.end(), object)
		   == objects_.end());
	objects_.push_back(object);
}

void Window::removeObject(Object* object)
{
	assert(object);
	const auto pos = std::remove(objects_.begin(), objects_.end(), object);
	objects_.erase(pos, objects_.end());
}

void Window::update()
{
	context_.activate();
	for(auto object : objects_)
	{
		assert(object);
		object->render();
	}
	context_.swapBuffers();
	context_.deactivate();
}

void Window::show()
{
	puts("[GKOM][Window] Showing...");
	glfwShowWindow(handle_);
}

void Window::hide()
{
	puts("[GKOM][Window] Hiding...");
	glfwHideWindow(handle_);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(handle_);
}

void Window::setShouldClose(bool shouldClose)
{
	printf("[GKOM][Window] Setting close flag to %d...\n", shouldClose);
	glfwSetWindowShouldClose(handle_, shouldClose);
}

void Window::setTitle(const char *title)
{
	assert(handle_);
	printf("[GKOM][Window] Setting title to %s...\n", title);
	glfwSetWindowTitle(handle_, title);
}

void Window::onKeyPress(KeyPressHandler keyPressHandler)
{
	if(!keyPressHandler)
	{
		glfwSetKeyCallback(handle_, nullptr);
		keyPressHandler_ = nullptr;
		puts("[GKOM][Window] Previous key press callback unregistered");
		return;
	}

	puts("[GKOM][Window] Registering key press callback...");
	keyPressHandler_ = std::move(keyPressHandler);
	glfwSetKeyCallback(handle_, keyCallback);
}

Window::Handle Window::handle() const noexcept
{
	return handle_;
}

void Window::releaseCallbacks()
{
	onKeyPress(nullptr);
	puts("[GKOM][Window] Callbacks released");
}

void Window::keyCallback(Window::Handle handle,
	             		 int key, int /*scancode*/,
	             		 int action, int mods)
{
	printf("[GKOM][Window] Key callback: hwnd=%p, key=%d, action=%d, mods=%d\n",
           handle, key, action, mods);

	auto window = detail::WindowsRegistry::at(handle);
	assert(window);
	if(action == GLFW_PRESS)
	{
		assert(window->keyPressHandler_);
		window->keyPressHandler_(key, mods);
	}
}

Window::Handle Window::createNative()
{
	puts("[GKOM][Window] Applying default window hints...");
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	puts("[GKOM][Window] Creating native...");
	constexpr auto width = 800;
	constexpr auto height = 600;
	constexpr auto title = "GKOM";
	constexpr auto monitor = static_cast<GLFWmonitor*>(nullptr);
	constexpr auto share = static_cast<GLFWwindow*>(nullptr);
	auto handle = glfwCreateWindow(width, height, title, monitor, share);
	if(handle == nullptr)
	{
		throw std::runtime_error("Could not create native window");
	}

	return handle;
}

} // gkom
