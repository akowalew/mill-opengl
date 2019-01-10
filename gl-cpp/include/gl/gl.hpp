#pragma once

#include "gl/FragmentShader.hpp"
#include "gl/VertexShader.hpp"
#include "gl/Program.hpp"
#include "gl/VertexArray.hpp"
#include "gl/VertexBuffer.hpp"
#include "gl/ElementBuffer.hpp"
#include "gl/Texture2D.hpp"

#include "glm/vec4.hpp"

namespace gl {

void init();

inline void enableCapability(GLenum capability)
{
	glEnable(capability);
}

inline void disableCapability(GLenum capability)
{
	glDisable(capability);
}

inline void setClearColor(const glm::vec4& color)
{
	glClearColor(color[0], color[1], color[2], color[3]);
}

inline void clearBuffers(GLbitfield mask)
{
	glClear(mask);
}

} // gl
