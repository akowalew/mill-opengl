#include "gkom/GeometryManager.hpp"

#include <algorithm>
#include <cassert>

#include "gkom/GraphicsManager.hpp"
#include "gkom/Geometry.hpp"
#include "gkom/Mesh.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

GeometryManager::GeometryManager(GraphicsManager& graphicsManager)
	:	graphicsManager_(graphicsManager)
	,	logger_(Logging::getLogger("GeometryManager"))
{
	logger_("Initialized");
}

GeometryManager::~GeometryManager() = default;

Geometry* GeometryManager::createGeometry(Mesh *mesh)
{
	assert(mesh != nullptr);

	const auto geometry = findGeometry(mesh);
	if(geometry != nullptr)
	{
		logger_("Reusing existing geometry...");
		return geometry;
	}

	const auto [pos, inserted] =
		geometries_.insert_or_assign(mesh, makeGeometry(mesh));
	assert(inserted);

	const auto& newGeometry = pos->second;
	assert(newGeometry != nullptr);
	return newGeometry.get();
}

Geometry* GeometryManager::findGeometry(Mesh *mesh)
{
	logger_("Looking for an existing geometry...");

	const auto pos = geometries_.find(mesh);
	if(pos == geometries_.end())
	{
		return nullptr;
	}

	const auto& geometry = pos->second;
	assert(geometry != nullptr);
	return geometry.get();
}

std::unique_ptr<Geometry> GeometryManager::makeGeometry(Mesh *mesh)
{
	assert(mesh != nullptr);
	assert(!mesh->positions.empty());

	auto geometry = std::make_unique<Geometry>();
	assert(geometry);

	const auto vertexArray = graphicsManager_.createVertexArray(mesh);
	assert(vertexArray != 0);
	geometry->vertexArray = vertexArray;

	if(mesh->indices.has_value())
	{
		geometry->withIndices = true;
		geometry->itemsCount = static_cast<int>(mesh->indices->size());
	}
	else
	{
		geometry->itemsCount = static_cast<int>(mesh->positions.size());
	}

	if(mesh->normals.has_value())
	{
		geometry->withNormals = true;
	}

	if(mesh->texcoords.has_value())
	{
		geometry->withTexcoords = true;
	}

	assert(geometry);
	return std::move(geometry);
}

} // gkom
