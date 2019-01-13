/**
 * main.cpp
 * @brief Entry point of the application
 */

#include "glfw/Application.hpp"
#include "glfw/Window.hpp"

int main(int /*argc*/, char** /*argv*/)
{
	glfw::Application app;
	glfw::Window window;
	window.show();
	return app.exec();
}




































// void GLAPIENTRY messageCallback(GLenum source,
// 								GLenum type,
// 								GLuint id,
// 								GLenum severity,
// 								GLsizei length,
// 								const GLchar* message,
// 								const void* userParam);

// int main(int /*argc*/, char** /*argv*/)
// {
// 	try
// 	{
// 		glfw::init();

// 		auto window = glfw::Window{};
// 		window.setTitle("ZW1-Mlyn");

// 		gl::enableCapability(GL_DEBUG_OUTPUT);
// 		glDebugMessageCallback(messageCallback, nullptr);

// 		// const auto backgroundColor = glm::vec4(0.1f, 0.0f, 0.0f, 1.0f);

// 		// const auto cameraPosition = glm::vec3(1.5f, 1.5f, 1.5f);
// 		// const auto centerPoint = glm::vec3(0.0f, 0.0f, 0.0f);
// 		// const auto upAxis = glm::vec3(0.0f, 0.0f, 1.0f);
// 		// auto fieldOfView = glm::radians(45.0f);
// 		// const auto aspectRatio = static_cast<float>(WindowWidth)
// 		                         // / static_cast<float>(WindowHeight);
// 		// const auto nearPlane = 0.5f;
// 		// const auto farPlane = 10.0f;


// void GLAPIENTRY messageCallback(GLenum /*source*/,
// 								GLenum type,
// 								GLuint /*id*/,
// 								GLenum severity,
// 								GLsizei /*length*/,
// 								const GLchar* message,
// 								const void* /*userParam*/)
// {
// 	fprintf( stderr, "[GL] %s type = 0x%x, severity = 0x%x, message = %s\n",
// 		   ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
// 			type, severity, message );
// 	assert(type != GL_DEBUG_TYPE_ERROR);
// }
