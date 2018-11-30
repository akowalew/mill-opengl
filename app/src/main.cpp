/**
 * main.cpp
 * @brief Entry point of the application
 */

#include <cstdio>
#include <stdexcept>
#include <array>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gl/gl.hpp"
#include "glfw/glfw.hpp"

constexpr auto WindowWidth = 800;
constexpr auto WindowHeight = 600;
constexpr auto WindowTitle = "ZW1-Mlyn";

const auto WindowHints =
	glfw::Window::Hints{{GLFW_SAMPLES, 4},
						{GLFW_CONTEXT_VERSION_MAJOR, 3},
						{GLFW_CONTEXT_VERSION_MINOR, 3},
						{GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
						{GLFW_RESIZABLE, GL_FALSE}};

#define BackgroundColor 0.1f, 0.0f, 0.0f, 1.0f

void GLAPIENTRY messageCallback(GLenum source,
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar* message,
								const void* userParam);

GLfloat vertices[] = {
//  Position      Color             Texcoords
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
};

GLuint elements[] = {
	0, 1, 2,
	2, 3, 0
};

int main(int /*argc*/, char** /*argv*/)
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration;
	using std::chrono::duration_cast;

	try
	{
		glfw::init();

		auto window = glfw::Window{WindowWidth, WindowHeight,
								   WindowTitle, WindowHints};

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(messageCallback, 0);

		auto vao = gl::VertexArray{};
		auto vbo = gl::VertexBuffer{vertices, GL_STATIC_DRAW};
		auto ebo = gl::ElementBuffer{elements, GL_STATIC_DRAW};
		auto vsh = gl::VertexShader{"res/main.vsh"};
		auto fsh = gl::FragmentShader{"res/main.fsh"};
		auto program = gl::Program{vsh, fsh};
		auto iipwTex = gl::Texture2D{"res/iipw.png"};
		auto positionAttr = gl::Attribute{0};
		auto colorAttr = gl::Attribute{1};
		auto texcoordAttr = gl::Attribute{2};
		auto transUni = program.getUniform("trans");

		iipwTex.setParams({{GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE},
						   {GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE},
						   {GL_TEXTURE_MIN_FILTER, GL_LINEAR},
						   {GL_TEXTURE_MAG_FILTER, GL_LINEAR}});

		positionAttr.setFormat(2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
		colorAttr.setFormat(3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 2 * sizeof(GLfloat));
		texcoordAttr.setFormat(2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 5 * sizeof(GLfloat));

		positionAttr.enable();
		colorAttr.enable();
		texcoordAttr.enable();

		float rotateSpeed = 1.0f;
		window.onKeyPress([&rotateSpeed](auto key, auto mods)
						  {
							  switch(key)
							  {
								  case GLFW_KEY_LEFT:
								      rotateSpeed = 2.0f;
								      break;
							      case GLFW_KEY_RIGHT:
								      rotateSpeed = -2.0f;
								      break;
							      default:
								      rotateSpeed = 1.0f;
								      break;
							  }
						  });

		auto startTime = high_resolution_clock::now();

		puts("[Application] Started");
		while(!window.shouldClose())
		{
			glfw::pollEvents();

			window.activate();
			glClearColor(BackgroundColor);
			glClear(GL_COLOR_BUFFER_BIT);

			auto timeNow = high_resolution_clock::now();
			auto timeDiff = duration_cast<duration<float>>(timeNow - startTime).count();
			auto trans = glm::rotate(glm::mat4{1.0f},
									 rotateSpeed * timeDiff * glm::radians(180.0f),
									 glm::vec3(0.0f, 0.0f, 1.0f));
			transUni.setValue(trans, GL_FALSE);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			window.display();
		}
	}
	catch(std::exception& ex)
	{
		printf("Exception occured: '%s'\n", ex.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void GLAPIENTRY messageCallback(GLenum source,
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar* message,
								const void* userParam)
{
	fprintf( stderr, "[GL] %s type = 0x%x, severity = 0x%x, message = %s\n",
		   ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
			type, severity, message );
	assert(type != GL_DEBUG_TYPE_ERROR);
}
