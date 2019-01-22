#include <cstdio>

#include <cassert>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/trigonometric.hpp>
#include <glm/gtx/transform.hpp>

#include "gkom/GraphicsManager.hpp"
#include "gkom/GeometryManager.hpp"
#include "gkom/ShaderLoader.hpp"
#include "gkom/ShapesFactory.hpp"
#include "gkom/MaterialsFactory.hpp"
#include "gkom/LightFactory.hpp"
#include "gkom/Camera.hpp"
#include "gkom/Window.hpp"
#include "gkom/Renderer.hpp"
#include "gkom/Entity.hpp"
#include "gkom/World.hpp"
#include "gkom/Scene.hpp"
#include "gkom/Geometry.hpp"

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
	camera.position = vec3{5.0f, 0.0f, 10.0f};
	camera.centerPoint = vec3{0.0f, 0.0f, 0.0f};
	camera.upAxis = vec3{0.0f, 1.0f, 0.0f};
	camera.fieldOfView = radians(45.0f);
	camera.nearPlane = 0.1f;
	camera.farPlane = 20.0f;

	World world;
	Scene scene;

	GraphicsManager graphicsManager;
	GeometryManager geometryManager{graphicsManager};
	ShapesFactory shapesFactory{world, geometryManager};
	ShaderLoader shaderLoader{graphicsManager};
	MaterialsFactory materialsFactory{shaderLoader};

	auto building = shapesFactory.createPrism(10);
	building->material = materialsFactory.createColorMaterial(vec3{0.2f, 0.3f, 0.0f});
	*building->transform =
		translate(vec3{0.0f, 0.0f, 0.0f})
			* rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
				* scale(vec3{1.0f, 1.0f, 1.0f});
	const auto buildingNode = scene.createNode();
	buildingNode->setEntity(building);

	const auto roof = shapesFactory.createBox();;
	roof->material = materialsFactory.createColorMaterial(vec3{1.0f, 0.3f, 0.1f});
	roof->transform =
		translate(vec3{0.0f, 2*0.5f, 0.0f})
			* rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
				* scale(vec3{1.0f, 1.0f, 1.0f});
	const auto roofNode = scene.createNode();
	roofNode->setEntity(roof);

	const auto mill = world.createEntity();
	mill->transform =
		translate(vec3{0.0f, 0.0f, 0.0f})
			* rotate(radians(45.0f), vec3(1.0f, 0.0f, 1.0f))
				* scale(vec3{1.0f, 1.0f, 1.0f});
	const auto millNode = scene.createNode();
	millNode->setEntity(mill);
	millNode->attachNode(roofNode);
	millNode->attachNode(buildingNode);

	LightFactory lightFactory(world);
	const auto lightPosition = vec3{5.0f, 5.0f, 5.0f};
	const auto lightColor = vec3{1.0f, 1.0f, 1.0f};
	const auto light = lightFactory.createLight(lightPosition, lightColor);

	Renderer renderer;
	renderer.setCamera(&camera);
	renderer.setBackgroundColor({0.1f, 0.1f, 0.2f});
	renderer.setScene(&scene);
	renderer.setLight(light);

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
