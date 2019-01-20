#include "gkom/PyramidFactory.hpp"

#include <cassert>

#include "gkom/GraphicsManager.hpp"
#include "gkom/Geometry.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

PyramidFactory::PyramidFactory(GraphicsManager& graphicsManager)
	:	graphicsManager_(graphicsManager)
	,	logger_(Logging::getLogger("PyramidFactory"))
{
	logger_("Initialized");
}

PyramidFactory::~PyramidFactory() = default;

Geometry* PyramidFactory::createPyramid()
{
	logger_("Looking for a pyramid geometry...");
	if(pyramid_)
	{
		return pyramid_.get();
	}

	logger_("Creating new pyramid geometry");
	pyramid_ = std::move(makePyramid());
	assert(pyramid_);
	return pyramid_.get();
}

std::unique_ptr<Geometry> PyramidFactory::makePyramid()
{
	const auto vertices = Vertices{
		// Basis
		{{-0.5f, -0.5f, 0.5f}},
		{{-0.5f, -0.5f, -0.5f}},
		{{0.5f, -0.5f, -0.5f}},
		{{0.5f, -0.5f, 0.5f}},

		// Corner
		{{0.0f, 0.5f, 0.0f}},
	};

	const auto indices = Indices{
		// Basis
		0, 1, 2,
		2, 3, 0,

		// Left face
		0, 4, 1,

		// Back face
		1, 4, 2,

		// Right face
		2, 4, 3,

		// Front face
		3, 4, 0,
	};

	const auto vertexArray =
		graphicsManager_.createVertexArray(vertices, indices);
	const auto indicesCount = static_cast<int>(indices.size());
	return std::make_unique<Geometry>(vertexArray, indicesCount);
}


} // gkom
