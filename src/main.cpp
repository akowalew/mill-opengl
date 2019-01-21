#include <cstdio>

#include <cassert>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/trigonometric.hpp>
#include <glm/gtx/transform.hpp>

#include "gkom/GraphicsManager.hpp"
#include "gkom/TransformManager.hpp"
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
	using namespace glm;

	Window window;
	window.setTitle("ZW1-Mlyn");
	window.setSize({1024, 768});
	window.activate();

	Camera camera;
	camera.position = vec3{0.0f, 0.0f, 10.0f};
	camera.centerPoint = vec3{0.0f, 0.0f, 0.0f};
	camera.upAxis = vec3{0.0f, 1.0f, 0.0f};
	camera.fieldOfView = radians(45.0f);
	camera.nearPlane = 0.1f;
	camera.farPlane = 20.0f;

	TransformManager transformManager;
	GraphicsManager graphicsManager;
	ShapesFactory shapesFactory(graphicsManager);
	ShaderLoader shaderLoader(graphicsManager);
	MaterialsFactory materialsFactory(shaderLoader);

	Renderer renderer;
	renderer.setCamera(&camera);
	renderer.setBackgroundColor({0.1f, 0.1f, 0.2f, 1.0f});

	World world;
	Scene scene;

	const auto building = world.createEntity();
	const auto buildingNode = scene.createNode();
	const auto buildingColor = vec4{0.2f, 0.3f, 0.0f, 1.0f};
	const auto buildingTf =
		translate(vec3{0.0f, 0.0f, 0.0f})
			// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
				* scale(vec3{2.0f, 2.0f, 1.0f});
	building->transform = transformManager.createTransform(buildingTf);
	building->geometry = shapesFactory.createBox();
	building->material = materialsFactory.createColorMaterial(buildingColor);
	buildingNode->setEntity(building);

	const auto roof = world.createEntity();
	const auto roofNode = scene.createNode();
	const auto roofColor = vec4{1.0f, 0.3f, 0.1f, 1.0f};
	const auto roofTf =
		translate(vec3{0.0f, 3*0.5f, 0.0f})
			// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
				* scale(vec3{2.0f, 1.0f, 1.0f});
	roof->transform = transformManager.createTransform(roofTf);
	roof->geometry = shapesFactory.createPyramid();
	roof->material = materialsFactory.createColorMaterial(roofColor);
	roofNode->setEntity(roof);

	const auto mill = world.createEntity();
	const auto millNode = scene.createNode();
	const auto millTf =
		translate(vec3{0.0f, 0.0f, 0.0f})
			* rotate(radians(45.0f), vec3(0.0f, 0.0f, 1.0f))
				* scale(vec3{0.5f, 0.5f, 0.5f});
	mill->transform = transformManager.createTransform(millTf);
	millNode->setEntity(mill);
	millNode->attachNode(roofNode);
	millNode->attachNode(buildingNode);

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
	            				camera.position[0] -= 0.25;
	            				break;

	            			case KeyCode::Left:
	            				camera.position[0] += 0.25;
	            				break;

	            			case KeyCode::Down:
	            				camera.position[2] += 0.1;
	            				break;

	            			case KeyCode::Up:
	            				camera.position[2] -= 0.1;
	            				break;

	            			case KeyCode::Subtract:
	            				camera.fieldOfView += radians(5.0f);
	            				break;

	            			case KeyCode::Add:
	            				camera.fieldOfView -= radians(5.0f);
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
