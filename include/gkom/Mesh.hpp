#pragma once

#include <cstdint>

namespace gkom {

class Mesh
{
public:
	Mesh(unsigned int vertexArray,
		 int indicesCount)
		:	vertexArray(vertexArray)
		,	indicesCount(indicesCount)
	{}

	unsigned int vertexArray {0};
	int indicesCount {-1};
};

} // gkom
