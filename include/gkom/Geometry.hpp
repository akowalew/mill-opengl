#pragma once

#include <cstdint>

namespace gkom {

class Geometry
{
public:
	Geometry() = default;

	Geometry(unsigned int vertexArray,
		     int itemsCount,
			 bool withIndices,
		     bool withNormals,
		     bool withTexcoords)
		:	vertexArray(vertexArray)
		,	itemsCount(itemsCount)
		,	withIndices(withIndices)
		,	withNormals(withNormals)
		,	withTexcoords(withTexcoords)
	{}

	unsigned int vertexArray {0};
	int itemsCount {-1};

	bool withIndices {false};
	bool withNormals {false};
	bool withTexcoords {false};
};

} // gkom
