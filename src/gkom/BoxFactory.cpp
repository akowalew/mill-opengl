#include "gkom/BoxFactory.hpp"

#include <cstdio>
#include <initializer_list>

#include "gkom/Geometry.hpp"
#include "gkom/Vertex.hpp"
#include "gkom/GraphicsManager.hpp"
#include "gkom/Logging.hpp"

#include <string.h>

namespace gkom {

BoxFactory::BoxFactory(GraphicsManager& graphicsManager)
	:	graphicsManager_(graphicsManager)
	,	logger_(Logging::getLogger("BoxFactory"))
{
	logger_("Initialized");
}

BoxFactory::~BoxFactory() = default;

Geometry* BoxFactory::createBox()
{
	if(!box_)
	{
		box_ = std::move(makeBox());
		assert(box_);
	}

	assert(box_);
	return box_.get();
}

std::unique_ptr<Geometry> BoxFactory::makeBox()
{
	logger_("Making box...");

	const auto vertices = Vertices{
		// Front face
		{{-0.5f, 0.5f, 0.5f}},
		{{0.5f, 0.5f, 0.5f}},
		{{-0.5f, -0.5f, 0.5f}},
		{{0.5f, -0.5f, 0.5f}},

		// Back face
		{{-0.5f, 0.5f, -0.5f}},
		{{0.5f, 0.5f, -0.5f}},
		{{-0.5f, -0.5f, -0.5f}},
		{{0.5f, -0.5f, -0.5f}},
	};

	const auto indices = Indices{
		0, 2, 1,
		1, 2, 3,
		5, 7, 4,
		4, 7, 6,
		4, 6, 0,
		0, 6, 2,
		1, 3, 5,
		5, 3, 7,
		4, 0, 5,
		5, 0, 1,
		2, 6, 3,
		3, 6, 7
	};

	const auto vertexArray =
		graphicsManager_.createVertexArray(vertices, indices);
	const auto indicesCount = static_cast<int>(indices.size());
	return std::make_unique<Geometry>(vertexArray, indicesCount);
}

} // gkom
