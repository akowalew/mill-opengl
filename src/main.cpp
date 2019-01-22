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
#include "gkom/Transform.hpp"

class MillFactory
{
public:
	MillFactory(gkom::World& world,
				gkom::Scene& scene,
				gkom::TransformManager& transformManager,
				gkom::ColorFactory& colorFactory,
				gkom::ShapesFactory& shapesFactory,
				gkom::MaterialsFactory& materialsFactory)
		:	world(world)
		,	scene(scene)
		,	transformManager(transformManager)
		,	colorFactory(colorFactory)
		,	shapesFactory(shapesFactory)
		,	materialsFactory(materialsFactory)
	{}

	gkom::Entity* createMill(gkom::SceneNode* parent = nullptr)
	{
		const auto mill = world.createEntity();
		const auto millNode = scene.createNode(parent);
		millNode->setEntity(mill);
		mill->transform = transformManager.createTransform();

		const auto building = createBuilding(millNode);
		*building->transform =
			(translate(glm::vec3{0.0f, 0.0f, 0.0f})
				* rotate(glm::radians(22.5f), glm::vec3{ 0.0f, 1.0f, 0.0f })
				* scale(glm::vec3{2.0f, 4.0f, 2.0f}));

		const auto roof = createRoof(millNode);
		*roof->transform =
			(translate(glm::vec3{0.0f, 2.75f, 0.0f})
				* rotate(glm::radians(22.5f), glm::vec3{ 0.0f, 1.0f, 0.0f })
				* scale(glm::vec3{2.0f, 1.5f, 2.0f}));

		const auto chimney = createChimney(millNode);
		*chimney->transform=
			(translate(glm::vec3{ 0.3f, +3.0f, 0.3f })
				* scale(glm::vec3{ 0.4f, 1.0f, 0.4f }));

		const auto step1 = createStep(millNode);
		*step1->transform =
			(translate(glm::vec3{ 0.0f, -0.4f, 1.5f })
				* scale(glm::vec3{ 0.8f, 0.2f, 1.0f }));

		const auto step2 = createStep(millNode);
		*step2->transform =
			(translate(glm::vec3{ 0.0f, -0.2f, 1.4f })
				* scale(glm::vec3{ 0.8f, 0.2f, 0.8f }));

		const auto step3 = createStep(millNode);
		*step3->transform =
			(translate(glm::vec3{ 0.0f, 0.0f, 1.3f })
				* scale(glm::vec3{ 0.8f, 0.2f, 0.6f }));

		const auto door = createDoor(millNode);
		*door->transform =
			(translate(glm::vec3{ 0.0f, +0.6f, 1.26f })
				* scale(glm::vec3{ 0.6f, 1.0f, 0.1f }));

		return mill;
	}

private:
	gkom::Entity* createBuilding(gkom::SceneNode* parent)
	{
		const auto building = world.createEntity();
		const auto buildingNode = scene.createNode(parent);
		buildingNode->setEntity(building);

		const auto buildingColor = glm::vec3{0.2f, 0.3f, 0.0f};
		building->transform = transformManager.createTransform();
		building->color = colorFactory.createColor(buildingColor);
		building->geometry = shapesFactory.createPrism(8);
		building->material = materialsFactory.createMaterial();
		return building;
	}

	gkom::Entity* createRoof(gkom::SceneNode* parent)
	{
		const auto roof = world.createEntity();
		const auto roofNode = scene.createNode(parent);
		roofNode->setEntity(roof);

		const auto roofColor = glm::vec3{1.0f, 0.3f, 0.1f};
		roof->transform = transformManager.createTransform();
		roof->color = colorFactory.createColor(roofColor);
		roof->geometry = shapesFactory.createCone(8);
		roof->material = materialsFactory.createMaterial();
		return roof;
	}

	gkom::Entity* createChimney(gkom::SceneNode* parent)
	{
		const auto chimney = world.createEntity();
		const auto chimneyNode = scene.createNode(parent);
		chimneyNode->setEntity(chimney);
		const auto chimneyColor = glm::vec3{ 1.0f, 0.0f, 0.0f };
		chimney->transform = transformManager.createTransform();
		chimney->color = colorFactory.createColor(chimneyColor);
		chimney->geometry = shapesFactory.createPrism(4);
		chimney->material = materialsFactory.createMaterial();
		return chimney;
	}

	gkom::Entity* createStep(gkom::SceneNode* parent)
	{
		const auto step = world.createEntity();
		const auto stepNode = scene.createNode(parent);
		stepNode->setEntity(step);

		const auto stepColor = glm::vec3{ 0.5f, 0.5f, 0.5f };
		step->transform = transformManager.createTransform();
		step->color = colorFactory.createColor(stepColor);
		step->geometry = shapesFactory.createPrism(4);
		step->material = materialsFactory.createMaterial();
		return step;
	}

	gkom::Entity* createDoor(gkom::SceneNode* parent)
	{
		const auto Door = world.createEntity();
		const auto DoorNode = scene.createNode(parent);
		DoorNode->setEntity(Door);

		const auto DoorColor = glm::vec3{ 0.0f, 0.0f, 0.0f };
		Door->transform = transformManager.createTransform();
		Door->color = colorFactory.createColor(DoorColor);
		Door->geometry = shapesFactory.createPrism(4);
		Door->material = materialsFactory.createMaterial();
		return Door;
	}

	gkom::World& world;
	gkom::Scene& scene;
	gkom::TransformManager& transformManager;
	gkom::ColorFactory& colorFactory;
	gkom::ShapesFactory& shapesFactory;
	gkom::MaterialsFactory& materialsFactory;
};

class PropellerFactory
{
public:
	PropellerFactory(gkom::World& world,
		gkom::Scene& scene,
		gkom::TransformManager& transformManager,
		gkom::ColorFactory& colorFactory,
		gkom::ShapesFactory& shapesFactory,
		gkom::MaterialsFactory& materialsFactory)
		: world(world)
		, scene(scene)
		, transformManager(transformManager)
		, colorFactory(colorFactory)
		, shapesFactory(shapesFactory)
		, materialsFactory(materialsFactory)
	{}

	gkom::Entity* createPropeller(gkom::SceneNode* parent = nullptr)
	{
		const auto mill = world.createEntity();
		const auto millNode = scene.createNode(parent);
		millNode->setEntity(mill);
		mill->transform = transformManager.createTransform();

		const auto connector = createConnector(millNode);
		*connector->transform =
			(translate(glm::vec3{ 0.0f, 1.0f, 0.36f })
				* rotate(glm::radians(90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f })
				* scale(glm::vec3{ 0.15f, 0.4f, 0.15f }));
		
		for (int i = 0; i < 7; i++) {
			const auto sail = createSail(millNode);
			*sail->transform =
				(translate(glm::vec3{ 0.0f, 1.0f, 0.5f })
					* rotate(glm::radians(360.0f/7*i), glm::vec3{ 0.0f, 0.0f, 1.0f })
					* translate(glm::vec3{ 0.0f, 0.45f, 0.0f })
					* scale(glm::vec3{ 0.1f, 0.9f, 0.1f }));
		}


		return mill;
	}

private:
	gkom::Entity* createConnector(gkom::SceneNode* parent)
	{
		const auto connector = world.createEntity();
		const auto connectorNode = scene.createNode(parent);
		connectorNode->setEntity(connector);

		const auto connectorColor = glm::vec3{ 0.5f, 0.5f, 0.0f };
		connector->transform = transformManager.createTransform();
		connector->color = colorFactory.createColor(connectorColor);
		connector->geometry = shapesFactory.createPrism(12);
		connector->material = materialsFactory.createMaterial();
		return connector;
	}

	gkom::Entity* createSail(gkom::SceneNode* parent)
	{
		const auto sail = world.createEntity();
		const auto sailNode = scene.createNode(parent);
		sailNode->setEntity(sail);

		const auto sailColor = glm::vec3{ 0.0f, 0.5f, 1.0f };
		sail->transform = transformManager.createTransform();
		sail->color = colorFactory.createColor(sailColor);
		sail->geometry = shapesFactory.createPrism(4);
		sail->material = materialsFactory.createMaterial();
		return sail;
	}


	gkom::World& world;
	gkom::Scene& scene;
	gkom::TransformManager& transformManager;
	gkom::ColorFactory& colorFactory;
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

	MillFactory millFactory{world, scene, transformManager,
							colorFactory, shapesFactory, materialsFactory};
	const auto mill = millFactory.createMill();
	*mill->transform =
		translate(vec3(0.0f, 0.0f, 0.0f))
			* scale(vec3(1.0f, 1.0f, 1.0f));

	PropellerFactory propellerFactory{ world, scene, transformManager,
							colorFactory, shapesFactory, materialsFactory };
	const auto propeller = propellerFactory.createPropeller();
	*propeller->transform =
		rotate(glm::radians(90), glm::vec3{ 1.0f, 0.0f, 0.0f })
		*translate(vec3(0.0f, 0.0f, 0.7f))
		* scale(vec3(1.5f, 1.5f, 1.5f));

	const auto grass = world.createEntity();
	const auto grassNode = scene.createNode();
	const auto grassColor = vec3{ 0.0f, 1.0f, 0.0f };
	const auto grassTf =
		translate(vec3{ 0.0f, -0.5f, 0.0f })
			* scale(vec3{ 30.0f, 0.01f, 30.0f });
	grass->transform = transformManager.createTransform(grassTf);
	grass->color = colorFactory.createColor(grassColor);
	grass->geometry = shapesFactory.createPrism(4);
	grass->material = materialsFactory.createMaterial();
	grassNode->setEntity(grass);


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
