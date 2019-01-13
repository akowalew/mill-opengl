#include "glfw/Window.hpp"

#include <algorithm>
#include <cassert>

#include <GLFW/glfw3.h>

#include "glfw/detail/WindowsRegistry.hpp"

namespace glfw {

Window::Window()
	:	handle_(createNative())
	,	context_(handle_)
{
	assert(handle_);
	detail::WindowsRegistry::add(this);
	listenSizeCallback();
	puts("[GLFW][Window] Initialized");
}

Window::~Window()
{
	if(handle_ != nullptr)
	{
		releaseCallbacks();
		detail::WindowsRegistry::remove(this);

		glfwDestroyWindow(handle_);
		puts("[GLFW][Window] Destroyed");
	}
}

Window::Window(Window&& other) noexcept
	:	handle_(std::move(other.handle_))
	,	context_(std::move(other.handle_))
	,	renderer_(std::move(other.renderer_))
{
	detail::WindowsRegistry::replace(&other, this);

	other.handle_ = nullptr;
	other.renderer_ = nullptr;
}

Window& Window::operator=(Window &&other) noexcept
{
	detail::WindowsRegistry::replace(&other, this);

	if(&other != this)
	{
		handle_ = std::move(other.handle_);
		context_ = std::move(other.context_);
		renderer_ = std::move(other.renderer_);

		other.handle_ = nullptr;
		other.renderer_ = nullptr;
	}

	return *this;
}

void Window::update()
{
	if(renderer_)
	{
		context_.activate();

		renderer_->onDraw();

		context_.swapBuffers();
		context_.deactivate();
	}
}

void Window::show()
{
	assert(handle_);
	puts("[GLFW][Window] Showing...");
	glfwShowWindow(handle_);
}

void Window::hide()
{
	assert(handle_);
	puts("[GLFW][Window] Hiding...");
	glfwHideWindow(handle_);
}

bool Window::shouldClose() const
{
	assert(handle_);
	return glfwWindowShouldClose(handle_);
}

void Window::setShouldClose(bool shouldClose)
{
	assert(handle_);
	printf("[GLFW][Window] Setting close flag to %d...\n", shouldClose);
	glfwSetWindowShouldClose(handle_, shouldClose);
}

void Window::setTitle(const char *title)
{
	assert(handle_);
	printf("[GLFW][Window] Setting title to %s...\n", title);
	glfwSetWindowTitle(handle_, title);
}

void Window::onKeyPress(KeyPressHandler keyPressHandler)
{
	assert(handle_);
	if(!keyPressHandler)
	{
		glfwSetKeyCallback(handle_, nullptr);
		keyPressHandler_ = nullptr;
		puts("[GLFW][Window] Previous key press callback unregistered");
		return;
	}

	puts("[GLFW][Window] Registering key press callback...");
	keyPressHandler_ = std::move(keyPressHandler);
	glfwSetKeyCallback(handle_, keyCallback);
}

void Window::setRenderer(Renderer *renderer)
{
	renderer_ = renderer;
	if(renderer_)
	{
		renderer_->onSurfaceCreated();
		renderer_->onSurfaceChanged(size());
	}
}

Size Window::size() const
{
	assert(handle_);
	Size size;
	glfwGetWindowSize(handle_, &size.width, &size.height);
	return size;
}

Window::Handle Window::handle() const noexcept
{
	return handle_;
}

void Window::listenSizeCallback()
{
	assert(handle_);
	puts("[GLFW][Window] Registering window size callback...");
	glfwSetWindowSizeCallback(handle_, sizeCallback);
}

void Window::releaseCallbacks()
{
	onKeyPress(nullptr);
	glfwSetWindowSizeCallback(handle_, nullptr);
	puts("[GLFW][Window] Callbacks released");
}

void Window::keyCallback(Window::Handle handle,
	             		 int key, int /*scancode*/,
	             		 int action, int mods)
{
	printf("[GLFW][Window] Key callback: hwnd=%p, key=%d, action=%d, mods=%d\n",
           static_cast<void*>(handle), key, action, mods);

	auto window = detail::WindowsRegistry::at(handle);
	assert(window);
	if(action == GLFW_PRESS)
	{
		assert(window->keyPressHandler_);
		window->keyPressHandler_(key, mods);
	}
}

void Window::sizeCallback(Window::Handle handle,
					      int width, int height)
{
	printf("[GLFW][Window] Size callback: hwnd=%p, width=%d, height=%d\n",
		   static_cast<void*>(handle), width, height);

	auto window = detail::WindowsRegistry::at(handle);
	assert(window);
	if(const auto renderer = window->renderer_; renderer)
	{
		renderer->onSurfaceChanged(Size{width, height});
	}
}

Window::Handle Window::createNative()
{
	puts("[GLFW][Window] Applying default window hints...");
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	puts("[GLFW][Window] Creating native...");
	constexpr auto width = 800;
	constexpr auto height = 600;
	constexpr auto title = "GLFW";
	constexpr auto monitor = static_cast<GLFWmonitor*>(nullptr);
	constexpr auto share = static_cast<GLFWwindow*>(nullptr);
	auto handle = glfwCreateWindow(width, height, title, monitor, share);
	if(handle == nullptr)
	{
		throw std::runtime_error("Could not create native window");
	}

	return handle;
}

} // glfw
