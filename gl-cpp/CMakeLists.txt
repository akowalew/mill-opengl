add_library(gl-cpp
	src/Shader.cpp include/gl/Shader.hpp
	src/Program.cpp include/gl/Program.hpp
	src/gl.cpp include/gl/gl.hpp
	src/glew.cpp include/gl/glew.hpp
)

set_target_properties(gl-cpp
	PROPERTIES
		CXX_STANDARD 17
		CXX_EXTENSIONS OFF
)

if(MSVC)
	target_compile_options(gl-cpp
		PRIVATE
			/W4
	)

else(MSVC)
	target_compile_options(gl-cpp
		PRIVATE
			-Wall -Wextra -pedantic
	)
endif(MSVC)

target_include_directories(gl-cpp
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(gl-cpp
	PUBLIC
		libglew_static
		SOIL_static
		glm_static
)
