#pragma once

#include "gl/Shader.hpp"

namespace gl {

class FragmentShader
	:	public Shader
{
public:
	FragmentShader()
		:	Shader(GL_FRAGMENT_SHADER)
	{}

	explicit FragmentShader(const char* path)
		:	Shader(path, GL_FRAGMENT_SHADER)
	{}
};

} // gl
