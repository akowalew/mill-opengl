#include "gkom/GeometryManager.hpp"

#include <algorithm>
#include <cassert>

#include "gkom/VertexArray.hpp"
#include "gkom/VertexBuffer.hpp"
#include "gkom/IndexBuffer.hpp"
#include "gkom/GraphicsManager.hpp"
#include "gkom/Geometry.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

GeometryManager::GeometryManager(GraphicsManager& graphicsManager)
	:	graphicsManager_(graphicsManager)
	,	logger_(Logging::getLogger("GeometryManager"))
{
	logger_("Initialized");
}

GeometryManager::~GeometryManager() = default;

Geometry
GeometryManager::createGeometry(const std::vector<glm::vec3>& positions,
						 	 	const std::vector<glm::vec3>& normals,
						 	 	const std::vector<unsigned int>& indices)
{
	assert(!positions.empty());
	assert(!normals.empty());
	assert(!indices.empty());

	auto positionsBuffer = loadPositions(positions);
	auto normalsBuffer = loadNormals(normals);
	auto indexBuffer = loadIndices(indices);

	logger_("Creating geometry...");
	auto vertexArray = graphicsManager_.createVertexArray();
	vertexArray.bind();
		indexBuffer.bind();

		positionsBuffer.bind();
		const auto positionsAttribute = 0;
		const auto positionsComponents = 3;
		const auto positionsStride = 6 * sizeof(float);
		const auto positionsOffset = 0 * sizeof(float);
		vertexArray.setAttributeFormat(positionsAttribute, positionsComponents,
									   positionsStride, positionsOffset);
		positionsBuffer.unbind();

		normalsBuffer.bind();
		const auto normalsAttribute = 1;
		const auto normalsComponents = 3;
		const auto normalsStride = 6 * sizeof(float);
		const auto normalsOffset = 3 * sizeof(float);
		vertexArray.setAttributeFormat(normalsAttribute, normalsComponents,
									   normalsStride, normalsOffset);
		normalsBuffer.unbind();
	vertexArray.unbind();
	indexBuffer.unbind();

	bool packed = false;
	return Geometry{vertexArray, static_cast<int>(indices.size()), packed};
}

Geometry
GeometryManager::createGeometry(const std::vector<Vertex>& vertices)
{
	assert(!vertices.empty());

	auto verticesBuffer = loadVertices(vertices);

	logger_("Creating geometry...");
	auto vertexArray = graphicsManager_.createVertexArray();
	vertexArray.bind();
		verticesBuffer.bind();
		const auto verticesAttribute = 0;
		const auto verticesComponents = 3;
		const auto verticesStride = 6 * sizeof(float);
		const auto verticesOffset = 0 * sizeof(float);
		vertexArray.setAttributeFormat(verticesAttribute, verticesComponents,
									   verticesStride, verticesOffset);

		const auto normalsAttribute = 1;
		const auto normalsComponents = 3;
		const auto normalsStride = 6 * sizeof(float);
		const auto normalsOffset = 3 * sizeof(float);
		vertexArray.setAttributeFormat(normalsAttribute, normalsComponents,
									   normalsStride, normalsOffset);
		verticesBuffer.unbind();
	vertexArray.unbind();

	bool packed = true;
	return Geometry{vertexArray, static_cast<int>(vertices.size()), packed};
}

VertexBuffer
GeometryManager::loadVertices(const std::vector<Vertex>& vertices)
{
	logger_("Loading vertices buffer...");
	auto verticesBuffer = graphicsManager_.createVertexBuffer();
	verticesBuffer.bind();
		verticesBuffer.loadData(vertices);
	verticesBuffer.unbind();
	return verticesBuffer;
}

VertexBuffer
GeometryManager::loadPositions(const std::vector<glm::vec3>& positions)
{
	logger_("Loading positions buffer...");
	auto positionsBuffer = graphicsManager_.createVertexBuffer();
	positionsBuffer.bind();
		positionsBuffer.loadData(positions);
	positionsBuffer.unbind();
	return positionsBuffer;
}

VertexBuffer
GeometryManager::loadNormals(const std::vector<glm::vec3>& normals)
{
	logger_("Loading normals buffer...");
	auto normalsBuffer = graphicsManager_.createVertexBuffer();
	normalsBuffer.bind();
		normalsBuffer.loadData(normals);
	normalsBuffer.unbind();
	return normalsBuffer;
}

IndexBuffer
GeometryManager::loadIndices(const std::vector<unsigned int>& indices)
{
	logger_("Loading indices buffer...");
	auto indexBuffer = graphicsManager_.createIndexBuffer();
	indexBuffer.bind();
		indexBuffer.loadData(indices);
	indexBuffer.unbind();
	return indexBuffer;
}

} // gkom
