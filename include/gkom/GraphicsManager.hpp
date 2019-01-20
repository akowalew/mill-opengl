#pragma once

#include <vector>
#include <memory>
#include <string_view>

#include "gkom/Vertex.hpp"

namespace gkom {

using Index = unsigned int;
using Vertices = std::vector<Vertex>;
using Indices = std::vector<Index>;

//! Forward declarations
class Logger;

class GraphicsManager
{
public:
	GraphicsManager();

	~GraphicsManager();

	unsigned int createVertexArray(const Vertices& vertices,
								   const Indices& indices);

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

	unsigned int createVertexArray();

	unsigned int createVertexBuffer(const std::vector<Vertex>& vertices);

	unsigned int createVertexBuffer();

	unsigned int createIndexBuffer(const std::vector<unsigned int>& indices);

	unsigned int createIndexBuffer();

	unsigned int generateBufferOnly();

	void storeIndices(const Indices& indices);

	void storeVertices(const Vertices& vertices);

	std::vector<unsigned int> vertexArrays_;
	std::vector<unsigned int> vertexBuffers_;
	std::vector<unsigned int> indexBuffers_;
	std::vector<unsigned int> textures_;
	std::vector<unsigned int> shaders_;
	std::vector<unsigned int> programs_;

	Logger& logger_;
};

} // gkom
