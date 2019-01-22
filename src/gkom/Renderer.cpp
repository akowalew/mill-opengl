#include "gkom/Renderer.hpp"

#include <functional>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "gkom/Entity.hpp"
#include "gkom/Geometry.hpp"
#include "gkom/Material.hpp"
#include "gkom/Logging.hpp"
#include "gkom/ShaderProgram.hpp"
#include "gkom/Uniform.hpp"
#include "gkom/VertexArray.hpp"
#include "gkom/Scene.hpp"
#include "gkom/Transform.hpp"

namespace gkom {

Renderer::Renderer()
	:	logger_(Logging::getLogger("Renderer"))
{
	glEnable(GL_DEPTH_TEST);

	logger_("Initialized");
}

void Renderer::render()
{
	if(scene_ == nullptr)
	{
		return; // No scene to render, go out
	}

	glClearColor(bgColor_[0], bgColor_[1], bgColor_[2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Transform transform;
	const auto rootNode = scene_->rootNode();
	assert(rootNode != nullptr);
	render(rootNode, transform);
}

void Renderer::render(SceneNode* node, const Transform& tf)
{
	assert(node != nullptr);
	const auto entity = node->entity();
	if(entity)
	{
		if(entity->transform)
		{
			const auto transform = (tf * (*entity->transform));
			render(entity, transform);
			for(const auto node : node->childNodes())
			{
				assert(node != nullptr);
				render(node, transform);
			}
		}
		else
		{
			render(entity, tf);
			for(const auto node : node->childNodes())
			{
				assert(node != nullptr);
				render(node, tf);
			}
		}
	}
	else
	{
		for(const auto node : node->childNodes())
		{
			assert(node != nullptr);
			render(node, tf);
		}
	}
}

void Renderer::render(Entity* entity, const Transform& transform)
{
	assert(entity != nullptr);
	assert(light_);

	const auto& geometry = entity->geometry;
	const auto& material = entity->material;

	if(!entity->geometry || !entity->material)
	{
		return; // Don't render object, which is not renderable
	}

	auto shaderProgram = ShaderProgram{material->shaderProgram};
	shaderProgram.use();
		auto projUniform = shaderProgram.getUniform("proj");
		auto viewUniform = shaderProgram.getUniform("view");
		auto transUniform = shaderProgram.getUniform("trans");
		auto lightPosition = shaderProgram.getUniform("lightPos");
		auto lightColor = shaderProgram.getUniform("lightColor");
		auto colorUniform = shaderProgram.getUniform("color");

		projUniform.loadMatrix(camera_->getProjection());
		viewUniform.loadMatrix(camera_->getView());
		transUniform.loadMatrix(transform);

		assert(light_->light);
		assert(light_->transform);

		const auto& lightCol = light_->light->color;
		lightColor.loadValue(lightCol);

		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		const auto& lightTransform = *light_->transform;
		glm::decompose(lightTransform, scale, rotation,
					   translation, skew, perspective);
		lightPosition.loadValue(translation);

		colorUniform.loadValue(entity->material->color);

		auto vertexArray = VertexArray{geometry->vertexArray};
		vertexArray.bind();
			vertexArray.enableAttribute(0);
			vertexArray.enableAttribute(1);
				assert(geometry->itemsCount != -1);
				if(geometry->packed)
				{
					glDrawArrays(GL_TRIANGLES, 0, geometry->itemsCount);
				}
				else
				{
					glDrawElements(GL_TRIANGLES, geometry->itemsCount,
								   GL_UNSIGNED_INT, 0);
				}

			vertexArray.disableAttribute(1);
			vertexArray.disableAttribute(0);
		vertexArray.unbind();
	shaderProgram.unuse();
}

void Renderer::surfaceChanged(int width, int height)
{
	logger_("Updating viewport...");
	glViewport(0, 0, width, height);

	logger_("Updating camera's aspect ratio...");
	camera_->aspectRatio = (static_cast<float>(width) / height);
}

void Renderer::setScene(Scene* scene)
{
	scene_ = scene;
}

Scene* Renderer::scene()
{
	return scene_;
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

void Renderer::setLight(Entity *light)
{
	light_ = light;
}

Entity* Renderer::light()
{
	return light_;
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
