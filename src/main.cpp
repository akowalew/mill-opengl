#include <cstdio>

#include <cassert>
#include <random>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/trigonometric.hpp>
#include <glm/gtx/transform.hpp>

#include "gkom/GraphicsManager.hpp"
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
	ShapesFactory shapesFactory(graphicsManager);
	ShaderLoader shaderLoader(graphicsManager);
	MaterialsFactory materialsFactory(shaderLoader);

	World world;
	Scene scene;

	const auto building = world.createEntity();
	const auto buildingNode = scene.createNode();
	const auto buildingColor = vec3{0.2f, 0.3f, 0.0f};
	const auto buildingTf =
		translate(vec3{0.0f, 0.0f, 0.0f})
			// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
				* scale(vec3{2.0f, 4.0f, 2.0f});
	building->transform = transformManager.createTransform(buildingTf);
	building->color = colorFactory.createColor(buildingColor);
	building->geometry = shapesFactory.createPrism(6);
	building->material = materialsFactory.createMaterial();
	buildingNode->setEntity(building);

	const auto roof = world.createEntity();
	const auto roofNode = scene.createNode();
	const auto roofColor = vec3{1.0f, 0.3f, 0.1f};
	const auto roofTf =
		translate(vec3{0.0f, 2.75f, 0.0f})
			// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
				* scale(vec3{2.0f, 1.5f, 2.0f});
	roof->transform = transformManager.createTransform(roofTf);
	roof->color = colorFactory.createColor(roofColor);
	roof->geometry = shapesFactory.createCone(6);
	roof->material = materialsFactory.createMaterial();
	//roofNode->setEntity(roof);

	const auto mill = world.createEntity();
	const auto millNode = scene.createNode();
	const auto millTf =
		translate(vec3{0.0f, 0.0f, 0.0f})
			//* rotate(radians(45.0f), vec3(1.0f, 0.0f, 1.0f))
				* scale(vec3{0.5f, 0.5f, 0.5f});
	mill->transform = transformManager.createTransform(millTf);
	millNode->setEntity(mill);
	millNode->attachNode(roofNode);
	//millNode->attachNode(buildingNode);

	const auto grass = world.createEntity();
	const auto grassNode = scene.createNode();
	const auto grassColor = vec3{ 0.0f, 1.0f, 0.0f };
	const auto grassTf =
		translate(vec3{ 0.0f, -0.5f, 0.0f })
		// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
		* scale(vec3{ 30.0f, 0.01f, 30.0f });
	grass->transform = transformManager.createTransform(grassTf);
	grass->color = colorFactory.createColor(grassColor);
	grass->geometry = shapesFactory.createPrism(4);
	grass->material = materialsFactory.createMaterial();
	grassNode->setEntity(grass);

	const auto chimney = world.createEntity();
	const auto chimneyNode = scene.createNode();
	const auto chimneyColor = vec3{ 1.0f, 0.0f, 0.0f };
	const auto chimneyTf =
		translate(vec3{ 0.3f, +1.35f, 0.3f })
		// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
		* scale(vec3{ 0.2f, 0.6f, 0.2f });
	chimney->transform = transformManager.createTransform(chimneyTf);
	chimney->color = colorFactory.createColor(chimneyColor);
	chimney->geometry = shapesFactory.createPrism(4);
	chimney->material = materialsFactory.createMaterial();
	//chimneyNode->setEntity(chimney);

	const auto step1 = world.createEntity();
	const auto step1Node = scene.createNode();
	const auto step1Color = vec3{ 0.5f, 0.5f, 0.5f };
	const auto step1Tf =
		translate(vec3{ 0.0f, -0.45f, 0.0f })
		// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
		* scale(vec3{ 0.2f, 0.1f, 0.5f });
	step1->transform = transformManager.createTransform(step1Tf);
	step1->color = colorFactory.createColor(step1Color);
	step1->geometry = shapesFactory.createPrism(4);
	step1->material = materialsFactory.createMaterial();
	//step1Node->setEntity(step1);

	const auto step2 = world.createEntity();
	const auto step2Node = scene.createNode();
	const auto step2Color = vec3{ 0.6f, 0.6f, 0.6f };
	const auto step2Tf =
		translate(vec3{ 0.0f, -0.35f, 0.05f })
		// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
		* scale(vec3{ 0.2f, 0.1f, 0.4f });
	step2->transform = transformManager.createTransform(step2Tf);
	step2->color = colorFactory.createColor(step2Color);
	step2->geometry = shapesFactory.createPrism(4);
	step2->material = materialsFactory.createMaterial();
	//step2Node->setEntity(step2);

	const auto step3 = world.createEntity();
	const auto step3Node = scene.createNode();
	const auto step3Color = vec3{ 0.7f, 0.7f, 0.7f };
	const auto step3Tf =
		translate(vec3{ 0.0f, -0.25f, 0.10f })
		// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
		* scale(vec3{ 0.2f, 0.1f, 0.3f });
	step3->transform = transformManager.createTransform(step3Tf);
	step3->color = colorFactory.createColor(step3Color);
	step3->geometry = shapesFactory.createPrism(4);
	step3->material = materialsFactory.createMaterial();
	//step3Node->setEntity(step3);

	const auto door = world.createEntity();
	const auto doorNode = scene.createNode();
	const auto doorColor = vec3{ 0.0f, 0.0f, 0.0f };
	const auto doorTf =
		translate(vec3{ 0.0f, -0.0f, 0.25f })
		// * rotate(radians(0.0f), vec3{0.0f, 1.0f, 0.0f})
		* scale(vec3{ 0.2f, 0.4f, 0.02f });
	door->transform = transformManager.createTransform(doorTf);
	door->color = colorFactory.createColor(doorColor);
	door->geometry = shapesFactory.createPrism(4);
	door->material = materialsFactory.createMaterial();
	//doorNode->setEntity(door);

	const auto connector = world.createEntity();
	const auto connectorNode = scene.createNode();
	const auto connectorColor = vec3{ 0.5f, 0.5f, 0.0f };
	const auto connectorTf =
		translate(vec3{ 0.0f, 0.0f, 0.10f })
		* rotate(radians(90.0f), vec3{ 1.0f, 0.0f, 0.0f })
		* scale(vec3{ 0.1f, 1.0f, 0.1f });
	connector->transform = transformManager.createTransform(connectorTf);
	connector->color = colorFactory.createColor(connectorColor);
	connector->geometry = shapesFactory.createPrism(12);
	connector->material = materialsFactory.createMaterial();
	connectorNode->setEntity(connector);

	Entity* createPropeller(SceneNode* parent)
	{
		auto propeller = world.createEntity();
		auto propellerNode = scene.createNode();
		auto propellerColor = vec3{ 0.7f, 0.7f, 0.7f };
		// Tworzysz pusty transform (0, 0, 0) pos, (1, 1, 1) scale, 
		propeller->transform = transformManager.createTransform();
		propeller->color = colorFactory.createColor(propellerColor);
		propeller->geometry = shapesFactory.createBox();
		propeller->material = materialsFactory.createMaterial();
		propellerNode->setEntity(propeller);
		parent->attachNode(propellerNode);
		return propeller;
	};

	for (int i = 0; i < 4; i++) {
		auto propeller = createPropeller(connectorNode);

		const auto propellerTransform =
			translate(vec3{ 0.0f, 0.0f, 0.10f })
			* rotate(radians(90.0f), vec3{ 1.0f, 0.0f, 0.0f })
			* scale(vec3{ 0.1f, 1.0f, 0.1f });
		*(propeller->transform) = propellerTransform;

	}

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
