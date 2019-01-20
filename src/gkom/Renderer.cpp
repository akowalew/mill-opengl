#include "gkom/Renderer.hpp"

#include <functional>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

#include "gkom/Entity.hpp"
#include "gkom/Mesh.hpp"
#include "gkom/Material.hpp"
#include "gkom/Logging.hpp"
#include "gkom/ShaderProgram.hpp"
#include "gkom/Uniform.hpp"
#include "gkom/VertexArray.hpp"

namespace gkom {

void
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

Renderer::Renderer()
	:	logger_(Logging::getLogger("Renderer"))
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	logger_("Initialized");
}

void Renderer::render(const std::vector<Entity*>& entities)
{
	glClearColor(bgColor_[0], bgColor_[1], bgColor_[2], bgColor_[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(const auto entity : entities)
	{
		assert(entity != nullptr);

		const auto& transform = entity->transform;
		const auto mesh = entity->mesh;
		const auto material = entity->material;
		if(mesh == nullptr || material == nullptr)
		{
			continue; // Don't render object, which are not renderable
		}

		auto shaderProgram = ShaderProgram{material->shaderProgram};
		shaderProgram.use();
			auto projUniform = shaderProgram.getUniform("proj");
			auto viewUniform = shaderProgram.getUniform("view");
			auto transUniform = shaderProgram.getUniform("trans");
			auto colorUniform = shaderProgram.getUniform("color");

			const auto proj = camera_->getProjection();
			const auto view = camera_->getView();
			const auto trans = transform.getMatrix();
			const auto& color = material->color;

			projUniform.loadMatrix(proj);
			viewUniform.loadMatrix(view);
			transUniform.loadMatrix(trans);
			colorUniform.loadValue(color);

			auto vertexArray = VertexArray{mesh->vertexArray};
			vertexArray.bind();
				vertexArray.enableAttribute(0);
				glDrawElements(GL_TRIANGLES, mesh->indicesCount,
							   GL_UNSIGNED_INT, 0);
				vertexArray.disableAttribute(0);
			vertexArray.unbind();
		shaderProgram.unuse();
	}
}

void Renderer::surfaceChanged(int width, int height)
{
	logger_("Updating viewport...");
	glViewport(0, 0, width, height);

	logger_("Updating camera's aspect ratio...");
	camera_->aspectRatio = (static_cast<float>(width) / height);
}

void Renderer::setCamera(Camera* camera)
{
	logger_("Setting camera...");

	const auto nextCamera = (camera != nullptr) ? camera : &defaultCamera_;
	if(camera_ != nullptr)
	{
		nextCamera->aspectRatio = camera_->aspectRatio;
	}

	camera_ = nextCamera;
}

Camera* Renderer::camera()
{
	return (camera_ == nullptr) ? &defaultCamera_ : camera_;
}

const Camera* Renderer::camera() const
{
	return (camera_ == nullptr) ? &defaultCamera_ : camera_;
}

void Renderer::setBackgroundColor(const Color& bgColor)
{
	logger_("Setting background color...");

	bgColor_ = bgColor;
}

const Color& Renderer::backgroundColor() const
{
	return bgColor_;
}

} // gkom
