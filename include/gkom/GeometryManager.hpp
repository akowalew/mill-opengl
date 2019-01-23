#pragma once

#include <vector>
#include <memory>

#include <glm/vec3.hpp>

namespace gkom {

class GraphicsManager;
class Logger;
struct Geometry;
class VertexBuffer;
class IndexBuffer;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
};

class GeometryManager
{
public:
	GeometryManager(GraphicsManager& graphicsManager);

	~GeometryManager();

	Geometry createGeometry(const std::vector<glm::vec3>& positions,
							const std::vector<glm::vec3>& normals,
							const std::vector<unsigned int>& indices);

	Geometry createGeometry(const std::vector<Vertex>& vertices);

private:
	VertexBuffer loadVertices(const std::vector<Vertex>& positions);
	VertexBuffer loadPositions(const std::vector<glm::vec3>& positions);
	VertexBuffer loadNormals(const std::vector<glm::vec3>& normals);
	IndexBuffer loadIndices(const std::vector<unsigned int>& indices);

	GraphicsManager& graphicsManager_;
	Logger& logger_;
};

} // gkom
