#include "gl/gl.hpp"

#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>

namespace gl {

void init()
{
	if(glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Could not initialize GLEW");
	}
}

} // namespace gl
