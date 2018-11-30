#pragma once

#include "gl/Shader.hpp"

namespace gl {

class VertexShader
	:	public Shader
{
public:
	VertexShader()
		:	Shader(GL_VERTEX_SHADER)
	{}

	explicit VertexShader(const char* path)
		:	Shader(path, GL_VERTEX_SHADER)
	{}
};

} // gl
