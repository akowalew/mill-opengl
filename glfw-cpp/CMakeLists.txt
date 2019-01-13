add_library(glfw-cpp
	src/detail/WindowsRegistry.cpp include/glfw/detail/WindowsRegistry.hpp
	src/Application.cpp include/glfw/Application.hpp
	src/Context.cpp include/glfw/Context.hpp
	src/Window.cpp include/glfw/Window.hpp
)

set_target_properties(glfw-cpp
	PROPERTIES
		CXX_STANDARD 17
		CXX_EXTENSIONS OFF
)

if(MSVC)
	target_compile_options(glfw-cpp
		PRIVATE
			/W4
	)

else(MSVC)
	target_compile_options(glfw-cpp
		PRIVATE
			-Wall -Wextra -pedantic
	)
endif(MSVC)

target_include_directories(glfw-cpp
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(glfw-cpp
	PRIVATE
		glfw
		gl-cpp
)
