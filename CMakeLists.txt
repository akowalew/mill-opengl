# Top-level project configuration
cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

project("ZW1-Mlyn")

add_subdirectory("submodules")

# Add main executable target

# Add 'resources' target - just copy them into build directory
add_custom_target(resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
)

add_executable(ZW1-Mlyn
	src/gkom/Window.cpp include/gkom/Window.hpp
	src/gkom/Logging.cpp include/gkom/Logging.hpp
	src/gkom/Camera.cpp include/gkom/Camera.hpp
	src/gkom/Scene.cpp include/gkom/Scene.hpp
	src/gkom/SceneNode.cpp include/gkom/SceneNode.hpp
	src/gkom/World.cpp include/gkom/World.hpp
	src/gkom/Color.cpp include/gkom/Color.hpp
	src/gkom/ColorFactory.cpp include/gkom/ColorFactory.hpp
	src/gkom/Transform.cpp include/gkom/Transform.hpp
	src/gkom/TransformManager.cpp include/gkom/TransformManager.hpp
	src/gkom/LightManager.cpp include/gkom/LightManager.hpp
	src/gkom/GraphicsManager.cpp include/gkom/GraphicsManager.hpp
	src/gkom/MaterialsFactory.cpp include/gkom/MaterialsFactory.hpp
	src/gkom/ShapesFactory.cpp include/gkom/ShapesFactory.hpp
	src/gkom/BoxFactory.cpp include/gkom/BoxFactory.hpp
	src/gkom/PyramidFactory.cpp include/gkom/PyramidFactory.hpp
	src/gkom/ConeFactory.cpp include/gkom/ConeFactory.hpp
	src/gkom/PrismFactory.cpp include/gkom/PrismFactory.hpp
	src/gkom/Renderer.cpp include/gkom/Renderer.hpp
	src/gkom/IndexBuffer.cpp include/gkom/IndexBuffer.hpp
	src/gkom/VertexBuffer.cpp include/gkom/VertexBuffer.hpp
	src/gkom/VertexArray.cpp include/gkom/VertexArray.hpp
	src/gkom/Texture.cpp include/gkom/Texture.hpp
	src/gkom/TextureLoader.cpp include/gkom/TextureLoader.hpp
	src/gkom/Shader.cpp include/gkom/Shader.hpp
	src/gkom/ShaderProgram.cpp include/gkom/ShaderProgram.hpp
	src/gkom/ShaderLoader.cpp include/gkom/ShaderLoader.hpp
	src/gkom/Uniform.cpp include/gkom/Uniform.hpp
	src/main.cpp
)

set_target_properties(ZW1-Mlyn PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)

target_include_directories(ZW1-Mlyn
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(ZW1-Mlyn
	PRIVATE
		libglew_static
		glfw
		glm_static
		SOIL_static
)

add_dependencies(ZW1-Mlyn
	resources
)
