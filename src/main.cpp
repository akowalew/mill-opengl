#include <cstdio>

#include <cassert>
#include <random>

#include <glm/trigonometric.hpp>

#include "gkom/GraphicsManager.hpp"
#include "gkom/ShaderLoader.hpp"
#include "gkom/ShapesFactory.hpp"
#include "gkom/MaterialsFactory.hpp"
#include "gkom/Camera.hpp"
#include "gkom/Window.hpp"
#include "gkom/Renderer.hpp"
#include "gkom/Entity.hpp"
#include "gkom/World.hpp"
#include "gkom/Scene.hpp"

int main()
{
	using namespace gkom;
	using namespace std::chrono;

	Window window;
	window.setTitle("ZW1-Mlyn");
	window.setSize({1024, 768});
	window.activate();

	Camera camera;
	camera.position = glm::vec3{1.5f, 1.5f, 1.5f};
	camera.fieldOfView = glm::radians(45.0f);
	camera.nearPlane = 1.0f;
	camera.farPlane = 10.0f;

	GraphicsManager graphicsManager;
	ShapesFactory shapesFactory(graphicsManager);
	ShaderLoader shaderLoader(graphicsManager);
	MaterialsFactory materialsFactory(shaderLoader);

	Renderer renderer;
	renderer.setCamera(&camera);
	renderer.setBackgroundColor({0.1f, 0.1f, 0.2f, 1.0f});

	World world;
	Scene scene;

	const auto sceneNode = scene.createNode();
	assert(sceneNode != nullptr);

	const auto entity1 = world.createEntity();
	assert(entity1 != nullptr);
	entity1->geometry = shapesFactory.createCone(20);
	entity1->material = materialsFactory.createColorMaterial(
		glm::vec4{1.0f, 0.0f, 0.0f, 1.0f});
	entity1->sceneNode = sceneNode;

	const auto entity2 = world.createEntity();
	assert(entity2 != nullptr);
	entity2->transform.scale[1] *= 2;
	entity2->transform.position[1] -= 1.5f;
	entity2->transform.rotation[0] = glm::radians(180.0f);
	entity2->geometry = shapesFactory.createCone(20);
	entity2->material = materialsFactory.createColorMaterial(
		glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});
	entity2->sceneNode = sceneNode;

	sceneNode->attachEntity(entity1);
	sceneNode->attachEntity(entity2);

	renderer.setScene(&scene);
	window.show();
	while(!window.shouldClose())
	{
		Event event;
		while(window.pollEvent(event))
		{
	        std::visit([&](auto&& ev) {
	            using T = std::decay_t<decltype(ev)>;
	            if constexpr (std::is_same_v<T, KeyEvent>)
	            {
	            	if(ev.action == KeyAction::Press
	            		|| ev.action == KeyAction::Repeat)
	            	{
	            		printf("[main] Key pressed: %d\n",
	            			   static_cast<int>(ev.code));

	            		switch(ev.code)
	            		{
	            			case KeyCode::Escape:
	            				window.setShouldClose(true);
	            				break;

	            			case KeyCode::Enter:
	            				break;

	            			case KeyCode::Right:
	            				camera.position[0] -= 0.1;
	            				break;

	            			case KeyCode::Left:
	            				camera.position[0] += 0.1;
	            				break;

	            			case KeyCode::Down:
	            				camera.position[2] += 0.1;
	            				break;

	            			case KeyCode::Up:
	            				camera.position[2] -= 0.1;
	            				break;

	            			case KeyCode::Subtract:
	            				camera.fieldOfView += glm::radians(5.0f);
	            				break;

	            			case KeyCode::Add:
	            				camera.fieldOfView -= glm::radians(5.0f);
	            				break;

	            			default:
	            				break;
	            		}
	            	}
	            }
	            else if constexpr (std::is_same_v<T, SizeEvent>)
	            {
	            	puts("[main] Window resized");
	            	renderer.surfaceChanged(ev.width, ev.height);
	            }
	        }, event);
		}

		renderer.render();
		window.update();
	}
}
