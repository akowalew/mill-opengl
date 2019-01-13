# Add main executable target

# # Add 'resources' target - just copy them into build directory
# add_custom_target(resources ALL
# 	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
# )

add_library(gkom
	src/Scene.cpp include/gkom/Scene.hpp
	src/Camera.cpp include/gkom/Camera.hpp
	src/Mesh.cpp include/gkom/Mesh.hpp

	src/geometry/Box.cpp include/gkom/geometry/Box.hpp
	src/geometry/Pyramid.cpp include/gkom/geometry/Pyramid.hpp
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
		SOIL_static
		gl-cpp
)

# add_dependencies(gkom
# 	resources
# )
