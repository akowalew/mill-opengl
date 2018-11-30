#include "gl/glew.hpp"

#include <stdexcept>

namespace glew {

void init()
{
	if(glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Could not initialize GLEW");
	}
}

} // glew
