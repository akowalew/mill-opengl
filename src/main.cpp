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
#include "gkom/Transform.hpp"

#define NUMBER_OF_SAILS 7

class MillFactory
{
public:
	MillFactory(gkom::World& world,
				gkom::Scene& scene,
				gkom::ShapesFactory& shapesFactory,
				gkom::MaterialsFactory& materialsFactory)
		:	world(world)
		,	scene(scene)
		,	shapesFactory(shapesFactory)
		,	materialsFactory(materialsFactory)
	{}

	gkom::Entity* createMill(gkom::SceneNode* parent = nullptr)
	{
		const auto mill = world.createEntity();
		const auto millNode = scene.createNode(parent);
		millNode->setEntity(mill);

		const auto building = createBuilding(millNode);
		building->transform =
			(translate(glm::vec3{0.0f, 1.0f, 0.0f})
				* rotate(glm::radians(22.5f), glm::vec3{ 0.0f, 1.0f, 0.0f })
				* scale(glm::vec3{2.0f, 4.0f, 2.0f}));

		const auto roof = createRoof(millNode);
		roof->transform =
			(translate(glm::vec3{0.0f, 3.75f, 0.0f})
				* rotate(glm::radians(22.5f), glm::vec3{ 0.0f, 1.0f, 0.0f })
				* scale(glm::vec3{2.0f, 1.5f, 2.0f}));

		const auto chimney = createChimney(millNode);
		chimney->transform=
			(translate(glm::vec3{ 0.3f, +4.0f, 0.3f })
				* scale(glm::vec3{ 0.4f, 1.0f, 0.4f }));

		const auto step1 = createStep(millNode);
		step1->transform =
			(translate(glm::vec3{ 0.0f, -0.4f, 1.5f })
				* scale(glm::vec3{ 0.8f, 0.2f, 1.0f }));

		const auto step2 = createStep(millNode);
		step2->transform =
			(translate(glm::vec3{ 0.0f, -0.2f, 1.4f })
				* scale(glm::vec3{ 0.8f, 0.2f, 0.8f }));

		const auto step3 = createStep(millNode);
		step3->transform =
			(translate(glm::vec3{ 0.0f, 0.0f, 1.3f })
				* scale(glm::vec3{ 0.8f, 0.2f, 0.6f }));

		const auto door = createDoor(millNode);
		door->transform =
			(translate(glm::vec3{ 0.0f, +0.6f, 1.26f })
				* scale(glm::vec3{ 0.6f, 1.0f, 0.1f }));

		return mill;
	}

private:
	gkom::Entity* createBuilding(gkom::SceneNode* parent)
	{
		const auto building = shapesFactory.createPrism(8);
		const auto buildingNode = scene.createNode(parent);
		buildingNode->setEntity(building);
		building->material = materialsFactory.createColorMaterial(glm::vec3{0.2f, 0.3f, 0.0f});
		return building;
	}

	gkom::Entity* createRoof(gkom::SceneNode* parent)
	{
		const auto roof = shapesFactory.createCone(8);
		const auto roofNode = scene.createNode(parent);
		roofNode->setEntity(roof);
		roof->material = materialsFactory.createColorMaterial(glm::vec3{1.0f, 0.3f, 0.1f});
		return roof;
	}

	gkom::Entity* createChimney(gkom::SceneNode* parent)
	{
		const auto chimney = shapesFactory.createBox();
		const auto chimneyNode = scene.createNode(parent);
		chimneyNode->setEntity(chimney);
		chimney->material = materialsFactory.createColorMaterial(glm::vec3{ 1.0f, 0.0f, 0.0f });
		return chimney;
	}

	gkom::Entity* createStep(gkom::SceneNode* parent)
	{
		const auto step = shapesFactory.createBox();
		const auto stepNode = scene.createNode(parent);
		stepNode->setEntity(step);
		const auto stepColor = glm::vec3{ 0.5f, 0.5f, 0.5f };
		step->material = materialsFactory.createColorMaterial(stepColor);
		return step;
	}

	gkom::Entity* createDoor(gkom::SceneNode* parent)
	{
		const auto Door = shapesFactory.createBox();
		const auto DoorNode = scene.createNode(parent);
		DoorNode->setEntity(Door);
		const auto DoorColor = glm::vec3{ 0.0f, 0.0f, 0.0f };
		Door->material = materialsFactory.createColorMaterial(DoorColor);
		return Door;
	}

	gkom::World& world;
	gkom::Scene& scene;
	gkom::ShapesFactory& shapesFactory;
	gkom::MaterialsFactory& materialsFactory;
};

class PropellerFactory
{
public:
	PropellerFactory(gkom::World& world,
		gkom::Scene& scene,
		gkom::ShapesFactory& shapesFactory,
		gkom::MaterialsFactory& materialsFactory)
		: world(world)
		, scene(scene)
		, shapesFactory(shapesFactory)
		, materialsFactory(materialsFactory)
	{}

	gkom::Entity* createPropeller(gkom::SceneNode* parent = nullptr)
	{
		const auto mill = world.createEntity();
		const auto millNode = scene.createNode(parent);
		millNode->setEntity(mill);

		const auto connector = createConnector(millNode);
		connector->transform =
			(translate(glm::vec3{ 0.0f, 1.0f, 0.36f })
				* rotate(glm::radians(90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f })
				* scale(glm::vec3{ 0.15f, 0.4f, 0.15f }));

		for (int i = 0; i < NUMBER_OF_SAILS; i++) {
			const auto sail = createSail(millNode);
			sail->transform =
				(translate(glm::vec3{ 0.0f, 1.0f, 0.5f })
					* rotate(glm::radians(360.0f/ NUMBER_OF_SAILS *i), glm::vec3{ 0.0f, 0.0f, 1.0f })
					* translate(glm::vec3{ 0.0f, 0.45f, 0.0f })
					* scale(glm::vec3{ 0.1f, 0.9f, 0.1f }));
		}

		return mill;
	}

private:
	gkom::Entity* createConnector(gkom::SceneNode* parent)
	{
		const auto connector = shapesFactory.createPrism(12);
		const auto connectorNode = scene.createNode(parent);
		connectorNode->setEntity(connector);

		const auto connectorColor = glm::vec3{ 0.5f, 0.5f, 0.0f };
		connector->material = materialsFactory.createColorMaterial(connectorColor);
		return connector;
	}

	gkom::Entity* createSail(gkom::SceneNode* parent)
	{
		const auto sail = shapesFactory.createBox();
		const auto sailNode = scene.createNode(parent);
		sailNode->setEntity(sail);

		const auto sailColor = glm::vec3{ 0.0f, 0.5f, 1.0f };
		sail->material = materialsFactory.createColorMaterial(sailColor);
		return sail;
	}

	gkom::World& world;
	gkom::Scene& scene;
	gkom::ShapesFactory& shapesFactory;
	gkom::MaterialsFactory& materialsFactory;
};

int main()
{
	using namespace gkom;
	using namespace std::chrono;
	using namespace glm;

	Window window;
	window.setTitle("ZW1-Mlyn");
	window.setSize({1024, 768});
	window.activate();
	float wind_speed = 10.0;

	Camera camera;
	camera.position = vec3{5.0f, 5.0f, 10.0f};
	camera.centerPoint = vec3{0.0f, 0.0f, 0.0f};
	camera.upAxis = vec3{0.0f, 1.0f, 0.0f};
	camera.fieldOfView = radians(45.0f);
	camera.nearPlane = 0.1f;
	camera.farPlane = 20.0f;

	World world;
	Scene scene;

	GraphicsManager graphicsManager;
	GeometryManager geometryManager(graphicsManager);
	ShapesFactory shapesFactory(world, geometryManager);
	ShaderLoader shaderLoader(graphicsManager);
	MaterialsFactory materialsFactory(shaderLoader);

	MillFactory millFactory{world, scene, shapesFactory, materialsFactory};
	const auto mill = millFactory.createMill();
	mill->transform =
		translate(vec3(0.0f, 0.0f, 0.0f))
			* scale(vec3(1.0f, 1.0f, 1.0f));

	PropellerFactory propellerFactory{ world, scene, shapesFactory, materialsFactory };
	const auto propeller = propellerFactory.createPropeller();
	propeller->transform =
		rotate(glm::radians(-90.0f), glm::vec3{ 0.0f, 1.0f, 0.0f })
			* translate(vec3(0.0f, 1.0f, 0.7f))
				* scale(vec3(1.5f, 1.5f, 1.5f));

	const auto grass = shapesFactory.createBox();
	const auto grassNode = scene.createNode();
	const auto grassColor = vec3{ 0.0f, 1.0f, 0.0f };
	grass->transform =
		translate(vec3{ 0.0f, -0.5f, 0.0f })
			* scale(vec3{ 3000.0f, 0.01f, 3000.0f });
	grass->material = materialsFactory.createColorMaterial(grassColor);
	grassNode->setEntity(grass);

	LightFactory lightFactory(world);
	const auto lightPosition = glm::vec3{5.0f, 5.0f, 5.0f};
	const auto lightColor = glm::vec3{1.0, 1.0, 1.0};
	auto light = lightFactory.createLight(lightPosition, lightColor);

	Renderer renderer;
	renderer.setCamera(&camera);
	renderer.setBackgroundColor({0.52f, 0.807f, 0.92f});
	renderer.setScene(&scene);
	renderer.setLight(light);
	auto begin = std::chrono::system_clock::now();

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
	            				camera.position[1] += 0.1;
	            				break;

	            			case KeyCode::Up:
	            				if(camera.position[1] > 0.1)
	            				{
		            				camera.position[1] -= 0.1;
	            				}
	            				break;

	            			case KeyCode::Subtract:
	            				camera.fieldOfView += radians(5.0f);
	            				break;

	            			case KeyCode::Add:
	            				camera.fieldOfView -= radians(5.0f);
	            				break;

	            			case KeyCode::W:
	            				light->transform = *light->transform
	            					* translate(glm::vec3{0.0f, 0.5f, 0.0f});
	            				break;

	            			case KeyCode::A:
	            				light->transform = *light->transform
	            					* translate(glm::vec3{-0.5f, 0.0f, 0.0f});
	            				break;

	            			case KeyCode::S:
	            				light->transform = *light->transform
	            					* translate(glm::vec3{0.0f, -0.5f, 0.0f});
	            				break;

	            			case KeyCode::D:
	            				light->transform = *light->transform
	            					* translate(glm::vec3{0.5f, 0.0f, 0.0f});
	            				break;

							case KeyCode::Y:
								wind_speed += 2;
								break;
							case KeyCode::Z:
								wind_speed -= 2;
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
		auto end = std::chrono::system_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count();
		propeller->transform = *propeller->transform
			*translate(vec3(0.0f, 1.0f, 0.0f))
			*rotate(glm::radians(float(wind_speed*diff)), glm::vec3{ 0.0f, 0.0f, 1.0f })
			*translate(vec3(0.0f, -1.0f, 0.0f));
		begin = end;
		renderer.render();
		window.update();
	}
}
