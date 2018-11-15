# Top-level project configuration

cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

project(opengl-tutorial)

## Add submodules needed by project
add_subdirectory(submodules)

## Add 'tutorial' executable
add_executable(tutorial
	src/main.cpp
	src/shprogram.cpp
)

### Set warning level for target
if (MSVC)
    target_compile_options(tutorial
    	PRIVATE
    		/W4 /WX
    )
else()
    target_compile_options(tutorial
    	PRIVATE
    		-Wall -Wextra -pedantic
    )
endif()

set_target_properties(tutorial
	PROPERTIES
		CXX_STANDARD 17
		CXX_EXTENSIONS OFF
)

target_include_directories(tutorial
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}/include
		${CMAKE_SOURCE_DIR}/submodules/Simple-OpenGL-Image-Library/src
		${CMAKE_CURRENT_SOURCE_DIR}/submodules/glm
)

target_link_libraries(tutorial
	PUBLIC
		glfw
		libglew_shared
		glm_shared
		SOIL
)

## Add 'resources' target - just copy them into build directory
add_custom_target(resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res
)
