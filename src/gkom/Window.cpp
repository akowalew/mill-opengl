#include "gkom/Window.hpp"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gkom/Logging.hpp"

namespace gkom {

Window::Window()
	:	handle_(createNative())
	,	logger_(Logging::getLogger("Window"))
{
	assert(handle_);
	glfwSetWindowUserPointer(handle_, this);
	setupCallbacks();
	setupContext();
}

Window::~Window()
{
	if(handle_ != nullptr)
	{
		releaseCallbacks();
		glfwSetWindowUserPointer(handle_, nullptr);
		glfwDestroyWindow(handle_);
		logger_("Destroyed");
	}
}

Window::Window(Window&& other) noexcept
	:	handle_(std::move(other.handle_))
	,	events_(std::move(other.events_))
	,	logger_(other.logger_)
{
	glfwSetWindowUserPointer(handle_, this);
	other.handle_ = nullptr;
}

Window& Window::operator=(Window &&other) noexcept
{
	if(&other != this)
	{
		handle_ = std::move(other.handle_);
		events_ = std::move(other.events_);
		glfwSetWindowUserPointer(handle_, this);

		other.handle_ = nullptr;
	}

	return *this;
}

void Window::activate()
{
	assert(handle_);
	glfwMakeContextCurrent(handle_);
}

void Window::deactivate()
{
	glfwMakeContextCurrent(nullptr);
}

void Window::show()
{
	assert(handle_);
	logger_("Showing...");
	glfwShowWindow(handle_);
}

void Window::hide()
{
	assert(handle_);
	logger_("Hiding...");
	glfwHideWindow(handle_);
}

bool Window::shouldClose() const
{
	assert(handle_);
	return glfwWindowShouldClose(handle_);
}

void Window::update()
{
	assert(handle_);
	glfwSwapBuffers(handle_);
}

bool Window::pollEvent(Event& event)
{
	if(popEvent(event))
	{
		return true;
	}

	glfwPollEvents();
	return popEvent(event);
}

bool Window::waitEvent(Event& event)
{
	if(popEvent(event))
	{
		return true;
	}

	glfwWaitEvents();
	return popEvent(event);
}

bool Window::waitEventFor(std::chrono::duration<double> timeout, Event& event)
{
	if(popEvent(event))
	{
		return true;
	}

	glfwWaitEventsTimeout(timeout.count());
	return popEvent(event);
}

void Window::setShouldClose(bool shouldClose)
{
	assert(handle_);
	logger_("Updating close flag...");
	glfwSetWindowShouldClose(handle_, shouldClose);
}

void Window::setSize(Size size)
{
	assert(handle_);
	glfwSetWindowSize(handle_, size.width, size.height);
}

void Window::setTitle(const char *title)
{
	assert(handle_);
	logger_("Updating title...");
	glfwSetWindowTitle(handle_, title);
}

Window::Handle Window::handle() const noexcept
{
	return handle_;
}

Size Window::size() const
{
	assert(handle_);
	Size size;
	glfwGetWindowSize(handle_, &size.width, &size.height);
	return size;
}

void Window::setupContext()
{
	logger_("Setting up context...");

	activate();
	glewExperimental = true;
	if(glewInit() != 0)
	{
		throw std::runtime_error("Could not initialize render device");
	}
	deactivate();
}

void Window::setupCallbacks()
{
	assert(handle_);
	logger_("Setting up callbacks...");
	glfwSetKeyCallback(handle_, keyCallback);
	glfwSetWindowSizeCallback(handle_, sizeCallback);
}

void Window::releaseCallbacks()
{
	glfwSetKeyCallback(handle_, nullptr);
	glfwSetWindowSizeCallback(handle_, nullptr);
	logger_("Callbacks released");
}

bool Window::popEvent(Event& event)
{
	if(events_.empty())
	{
		return false;
	}

	event = std::move(events_.front());
	events_.pop_front();
	return true;
}

void Window::keyCallback(Window::Handle handle,
	             		 int key, int /*scancode*/,
	             		 int action, int /*mods*/)
{
	// logger_("Key callback");
	const auto window = static_cast<Window*>(glfwGetWindowUserPointer(handle));
	assert(window);

	const auto event = KeyEvent{KeyCode{key}, KeyAction{action}};
	window->events_.emplace_back(event);
}

void Window::sizeCallback(Window::Handle handle,
					      int width, int height)
{
	// logger_("Size callback");
	const auto window = static_cast<Window*>(glfwGetWindowUserPointer(handle));
	assert(window);
	window->events_.emplace_back(SizeEvent{width, height});
}

Window::Handle Window::createNative()
{
	// logger_("Applying default window hints...");
	glfwInit();
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// logger_("Creating native...");
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

} // gkom
