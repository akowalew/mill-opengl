#include "gkom/GraphicsManager.hpp"

#include <cstdio>
#include <cassert>

#define GLEW_STATIC
#include <GL/glew.h>

#include "gkom/VertexArray.hpp"
#include "gkom/VertexBuffer.hpp"
#include "gkom/IndexBuffer.hpp"
#include "gkom/Texture.hpp"
#include "gkom/Shader.hpp"
#include "gkom/ShaderProgram.hpp"
#include "gkom/Logging.hpp"
#include "gkom/Mesh.hpp"

namespace gkom {

GraphicsManager::GraphicsManager()
	:	logger_(Logging::getLogger("GraphicsManager"))
{
	logger_("Initialized");
}

GraphicsManager::~GraphicsManager()
{
	glDeleteVertexArrays(vertexArrays_.size(), vertexArrays_.data());
	glDeleteBuffers(vertexBuffers_.size(), vertexBuffers_.data());
	glDeleteBuffers(indexBuffers_.size(), indexBuffers_.data());
	glDeleteTextures(textures_.size(), textures_.data());

	for(const auto shader : shaders_)
	{
		glDeleteShader(shader);
	}

	for(const auto program : programs_)
	{
		glDeleteProgram(program);
	}

	logger_("Destroyed");
}

unsigned int
GraphicsManager::createVertexArray(Mesh* mesh)
{
	assert(mesh != nullptr);

	// Shouldn't this be done inside geometry manager?

	logger_("Creating vertex array...");
	auto vertexArray = VertexArray{createVertexArray()};
	vertexArray.bind();

		logger_("Creating position buffer...");
		assert(!mesh->positions.empty());
		auto positionBuffer = VertexBuffer{createVertexBuffer()};
		positionBuffer.bind();
			positionBuffer.loadData(mesh->positions);
			const auto positionStride = 3 * sizeof(GLfloat);
			const auto positionOffset = static_cast<void*>(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false,
								  positionStride, positionOffset);
		positionBuffer.unbind();

		if(mesh->indices)
		{
			logger_("Creating indices buffer...");
			assert(!mesh->indices->empty());
			auto indexBuffer = IndexBuffer{createIndexBuffer()};
			indexBuffer.bind();
				indexBuffer.loadData(*mesh->indices);
			// TODO: Should be here unbind?
		}

		if(mesh->normals)
		{
			logger_("Creating normals buffer...");
			assert(!mesh->normals->empty());
			auto normalsBuffer = VertexBuffer{createVertexBuffer()};
			normalsBuffer.bind();
				normalsBuffer.loadData(*mesh->normals);
				const auto normalsStride = 3 * sizeof(GLfloat);
				const auto normalsOffset = static_cast<void*>(0);
				glVertexAttribPointer(1, 3, GL_FLOAT, false, normalsStride, normalsOffset);
			normalsBuffer.unbind();
		}

	vertexArray.unbind();
	return vertexArray;
}

unsigned int
GraphicsManager::createShaderProgram(std::string_view vshCode,
									 std::string_view fshCode)
{
	logger_("Creating vertex shader...");
	const auto vsh = createShader(GL_VERTEX_SHADER, vshCode);

	logger_("Creating fragment shader...");
	const auto fsh = createShader(GL_FRAGMENT_SHADER, fshCode);

	return createShaderProgram(vsh, fsh);
}

unsigned int
GraphicsManager::createTexture(int levelOfDetail,
							   int width, int height,
							   const unsigned char* data)
{
	auto texture = Texture{createTexture()};

	logger_("Loading image into texture...");
	texture.loadImage(levelOfDetail, width, height, data);
	return texture;
}

unsigned int
GraphicsManager::createShader(unsigned int type, std::string_view code)
{
	auto shader = Shader{createShader(type)};

	logger_("Loading source into shader...");
	shader.loadSource(code.data(), code.size());

	logger_("Compiling shader...");
	shader.compile();
	return shader;
}

unsigned int
GraphicsManager::createShader(unsigned int type)
{
	logger_("Creating shader...");
	const auto shader = glCreateShader(type);
	if(shader == 0)
	{
		throw std::runtime_error("Could not create vertex shader");
	}

	shaders_.emplace_back(shader);
	return shader;
}

unsigned int
GraphicsManager::createShaderProgram(unsigned int vertexShader,
									 unsigned int fragmentShader)
{
	auto shprogram = ShaderProgram{createShaderProgram()};
	const auto vsh = Shader{vertexShader};
	const auto fsh = Shader{fragmentShader};

	logger_("Attaching shaders into program...");
	shprogram.attach(vsh);
	shprogram.attach(fsh);

	logger_("Linking shader program...");
	shprogram.link();
	return shprogram;
}

unsigned int
GraphicsManager::createShaderProgram()
{
	logger_("Creating shader program...");
	const auto program = glCreateProgram();
	if(program == 0)
	{
		throw std::runtime_error("Could not create program");
	}

	programs_.emplace_back(program);
	return program;
}


unsigned int
GraphicsManager::createTexture()
{
	logger_("Creating texture...");
	unsigned int texture = 0;
	glGenTextures(1, &texture);
	if(texture == 0)
	{
		throw std::runtime_error("Could not load texture");
	}

	textures_.emplace_back(texture);
	return texture;
}

// unsigned int
// GraphicsManager::createVertexBuffer(const std::vector<Vertex>& vertices)
// {
// 	auto vertexBuffer = VertexBuffer{createVertexBuffer()};

// 	logger_("Loading data into vertex buffer...");
// 	vertexBuffer.bind();
// 	vertexBuffer.loadData(vertices);
// 	vertexBuffer.unbind();
// 	return vertexBuffer;
// }

// unsigned int
// GraphicsManager::createIndexBuffer(const std::vector<unsigned int>& indices)
// {
// 	auto indexBuffer = IndexBuffer{createIndexBuffer()};

// 	logger_("Loading data into index buffer...");
// 	indexBuffer.bind();
// 	indexBuffer.loadData(indices);
// 	indexBuffer.unbind();
// 	return indexBuffer;
// }


unsigned int GraphicsManager::createVertexArray()
{
	logger_("Creating vertex array...");
	unsigned int vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	if(vertexArray == 0)
	{
		throw std::runtime_error("Could not generate vertex array");
	}

	vertexArrays_.emplace_back(vertexArray);
	return vertexArray;
}

unsigned int GraphicsManager::createVertexBuffer()
{
	logger_("Creating vertex buffer...");
	const auto vertexBuffer = generateBufferOnly();
	vertexBuffers_.emplace_back(vertexBuffer);
	return vertexBuffer;
}

unsigned int GraphicsManager::createIndexBuffer()
{
	logger_("Creating index buffer...");
	const auto indexBuffer = generateBufferOnly();
	indexBuffers_.emplace_back(indexBuffer);
	return indexBuffer;
}

unsigned int GraphicsManager::generateBufferOnly()
{
	unsigned int buffer = 0;
	glGenBuffers(1, &buffer);
	if(buffer == 0)
	{
		throw std::runtime_error("Could not generate buffer");
	}

	return buffer;
}

} // gkom
