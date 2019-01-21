#include <cstdio>

#include <cassert>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/trigonometric.hpp>
#include <glm/gtx/transform.hpp>

#include "gkom/GraphicsManager.hpp"
#include "gkom/GeometryManager.hpp"
#include "gkom/ColorFactory.hpp"
#include "gkom/TransformManager.hpp"
#include "gkom/ShaderLoader.hpp"
#include "gkom/ShapesFactory.hpp"
#include "gkom/MaterialsFactory.hpp"
#include "gkom/LightManager.hpp"
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
	camera.position = vec3{5.0f, 0.0f, 10.0f};
	camera.centerPoint = vec3{0.0f, 0.0f, 0.0f};
	camera.upAxis = vec3{0.0f, 1.0f, 0.0f};
	camera.fieldOfView = radians(45.0f);
	camera.nearPlane = 0.1f;
	camera.farPlane = 20.0f;

	ColorFactory colorFactory;
	TransformManager transformManager;
	GraphicsManager graphicsManager;
	GeometryManager geometryManager{graphicsManager};
	ShapesFactory shapesFactory;
	ShaderLoader shaderLoader{graphicsManager};
	MaterialsFactory materialsFactory{shaderLoader};

	World world;
	Scene scene;

	const auto building = world.createEntity();
	const auto buildingNode = scene.createNode();
	const auto buildingColor = vec3{0.2f, 0.3f, 0.0f};
	const auto buildingMesh = shapesFactory.createBoxWithNormals();
	const auto buildingTf =
		translate(vec3{0.0f, 0.0f, 0.0f})
			// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
				* scale(vec3{1.0f, 1.0f, 1.0f});
	building->transform = transformManager.createTransform(buildingTf);
	building->color = colorFactory.createColor(buildingColor);
	building->geometry = geometryManager.createGeometry(buildingMesh);
	building->material = materialsFactory.createMaterial();
	buildingNode->setEntity(building);

	const auto roof = world.createEntity();
	const auto roofNode = scene.createNode();
	const auto roofColor = vec3{1.0f, 0.3f, 0.1f};
	const auto roofMesh = shapesFactory.createBoxWithNormals();
	const auto roofTf =
		translate(vec3{0.0f, 2*0.5f, 0.0f})
			// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
				* scale(vec3{1.0f, 1.0f, 1.0f});
	roof->transform = transformManager.createTransform(roofTf);
	roof->color = colorFactory.createColor(roofColor);
	roof->geometry = geometryManager.createGeometry(roofMesh);
	roof->material = materialsFactory.createMaterial();
	roofNode->setEntity(roof);

	const auto mill = world.createEntity();
	const auto millNode = scene.createNode();
	const auto millTf =
		translate(vec3{0.0f, 0.0f, 0.0f})
			* rotate(radians(45.0f), vec3(1.0f, 0.0f, 1.0f))
				* scale(vec3{1.0f, 1.0f, 1.0f});
	mill->transform = transformManager.createTransform(millTf);
	millNode->setEntity(mill);
	millNode->attachNode(roofNode);
	millNode->attachNode(buildingNode);

	LightManager lightManager(world, transformManager, colorFactory);
	const auto lightPosition = vec3{5.0f, 5.0f, 5.0f};
	const auto lightColor = vec3{1.0f, 1.0f, 1.0f};
	const auto light = lightManager.createLight(lightPosition, lightColor);

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
