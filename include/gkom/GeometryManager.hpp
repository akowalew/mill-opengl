#pragma once

#include <unordered_map>
#include <memory>

namespace gkom {

class GraphicsManager;
class Mesh;
class Logger;
class Geometry;

class GeometryManager
{
public:
	GeometryManager(GraphicsManager& graphicsManager);

	~GeometryManager();

	Geometry* createGeometry(Mesh* mesh);

	Geometry* findGeometry(Mesh* mesh);

private:
	std::unique_ptr<Geometry> makeGeometry(Mesh* mesh);

	std::unordered_map<Mesh*, std::unique_ptr<Geometry>> geometries_;
	GraphicsManager& graphicsManager_;
	Logger& logger_;
};

} // gkom
