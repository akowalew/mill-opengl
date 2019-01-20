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

class EntityGenerator
{
public:
	gkom::World& world;
	gkom::GraphicsManager& graphicsManager;
	gkom::ShapesFactory& shapesFactory;
	gkom::MaterialsFactory& materialsFactory;

	std::vector<gkom::Entity*> operator()(int count) const
	{
		using namespace gkom;
		assert(count > 0);

	    std::random_device rdevice;
	    std::default_random_engine rengine(rdevice());
	    std::uniform_real_distribution<float> positionDist(0.0, 1.0);
	    std::uniform_real_distribution<float> scaleDist(0.1, 0.2);
	    std::uniform_real_distribution<float> rotationDist(0.1, 0.3);
	    std::uniform_real_distribution<float> colorDist(0.0, 1.0);

		std::vector<Entity*> entities;
		for(auto i = 0; i < count; ++i)
		{
			const auto px = positionDist(rengine);
			const auto py = positionDist(rengine);
			const auto pz = positionDist(rengine);
			const auto position = glm::vec3{px, py, pz};

			const auto sx = scaleDist(rengine);
			const auto sy = sx;
			const auto sz = sx;
			const auto scale = glm::vec3{sx, sy, sz};

			const auto rx = glm::radians(rotationDist(rengine) * 360.0f);
			const auto ry = glm::radians(rotationDist(rengine) * 360.0f);
			const auto rz = glm::radians(rotationDist(rengine) * 360.0f);
			const auto rotation = glm::vec3{rx, ry, rz};

			const auto red = colorDist(rengine);
			const auto green = colorDist(rengine);
			const auto blue = colorDist(rengine);
			const auto alpha = 1.0f;
			const auto color = glm::vec4(red, green, blue, alpha);

			const auto entity = world.createEntity();
			assert(entity != nullptr);
			entity->transform = Transform{position, scale, rotation};
			entity->geometry = shapesFactory.createCone(20);
			entity->material = materialsFactory.createColorMaterial(color);
			entities.emplace_back(entity);
		}

		return entities;
	}
};

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

	Renderer renderer;
	renderer.setCamera(&camera);
	renderer.setBackgroundColor({0.1f, 0.1f, 0.2f, 1.0f});

	GraphicsManager graphicsManager;
	ShapesFactory shapesFactory(graphicsManager);
	ShaderLoader shaderLoader(graphicsManager);
	MaterialsFactory materialsFactory(shaderLoader);

	World world;
	EntityGenerator entityGenerator{world, graphicsManager,
									shapesFactory, materialsFactory};

	const auto entitiesCount = 10;
	auto entities = entityGenerator(entitiesCount);

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
	            				world.clear();
	            				entities = entityGenerator(entitiesCount);
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

		renderer.render(entities);
		window.update();
	}
}
