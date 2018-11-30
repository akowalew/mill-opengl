add_library(glfw-cpp
	src/glfw.cpp
	src/Window.cpp

	include/glfw/glfw.hpp
	include/glfw/Window.hpp
)

set_target_properties(glfw-cpp
	PROPERTIES
		CXX_STANDARD 17
		CXX_EXTENSIONS OFF
)

target_include_directories(glfw-cpp
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(glfw-cpp
	PUBLIC
		gl-cpp

		glfw
)
