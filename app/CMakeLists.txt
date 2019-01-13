# Add main executable target

# Add 'resources' target - just copy them into build directory
# add_custom_target(resources ALL
# 	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
# )

add_executable(ZW1-Mlyn
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
		gkom
		glfw-cpp
		# glm_static
		# SOIL_static
)

# add_dependencies(ZW1-Mlyn
# 	resources
# )
