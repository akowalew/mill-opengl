#pragma once

#include <vector>
#include <memory>
#include <string_view>

#include <glm/vec3.hpp>

namespace gkom {

//! Forward declarations
class Logger;
class VertexArray;
class VertexBuffer;
class IndexBuffer;

class GraphicsManager
{
public:
	GraphicsManager();

	~GraphicsManager();

	VertexArray createVertexArray();

	VertexBuffer createVertexBuffer();

	IndexBuffer createIndexBuffer();

	unsigned int createShaderProgram(std::string_view vertexShaderCode,
							         std::string_view fragmentShaderCode);

	unsigned int createTexture(int levelOfDetail,
						       int width, int height,
						       const unsigned char* data);

private:
	unsigned int createShader(unsigned int type);

	unsigned int createShader(unsigned int type, std::string_view code);

	unsigned int createShaderProgram();

	unsigned int createShaderProgram(unsigned int vertexShader,
									 unsigned int fragmentShader);

	unsigned int createTexture();

	unsigned int createBuffer();

	std::vector<unsigned int> vertexArrays_;
	std::vector<unsigned int> buffers_;
	std::vector<unsigned int> textures_;
	std::vector<unsigned int> shaders_;
	std::vector<unsigned int> programs_;

	Logger& logger_;
};

} // gkom
