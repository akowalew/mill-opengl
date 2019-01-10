# Add main executable target

# # Add 'resources' target - just copy them into build directory
# add_custom_target(resources ALL
# 	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
# )

add_library(gkom
	src/detail/WindowsRegistry.cpp include/gkom/detail/WindowsRegistry.hpp

	src/Application.cpp include/gkom/Application.hpp
	src/Window.cpp include/gkom/Window.hpp
	src/Context.cpp include/gkom/Context.hpp
	src/Scene.cpp include/gkom/Scene.hpp
	src/Camera.cpp include/gkom/Camera.hpp
	src/World.cpp include/gkom/World.hpp

	src/Box.cpp include/gkom/Box.hpp
)

set_target_properties(gkom PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)

target_include_directories(gkom
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(gkom
	PUBLIC
		glm_static
	PRIVATE
		libglew_static
		glfw
		SOIL_static
		gl-cpp
)

# add_dependencies(gkom
# 	resources
# )
