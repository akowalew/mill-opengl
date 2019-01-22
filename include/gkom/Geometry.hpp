#pragma once

#include "gkom/VertexArray.hpp"
#include "gkom/IndexBuffer.hpp"

namespace gkom {

//! Component
class Geometry
{
public:
	Geometry() = default;

	Geometry(VertexArray vertexArray,
		     int itemsCount,
		     bool packed)
		:	vertexArray(vertexArray)
		,	itemsCount(itemsCount)
		,	packed(packed)
	{}

	VertexArray vertexArray;
	int itemsCount {-1};
	bool packed {false};
};

} // gkom
