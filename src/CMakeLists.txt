# Add main executable target

add_executable(ZW1-Mlyn
	main.cpp
	shprogram.cpp shprogram.h
)

set_target_properties(ZW1-Mlyn PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)

target_include_directories(ZW1-Mlyn
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ZW1-Mlyn
	glm_static
	glfw
	libglew_static
	SOIL_static
)

add_dependencies(ZW1-Mlyn
	resources
)
