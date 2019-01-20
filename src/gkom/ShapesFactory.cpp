#include "gkom/ShapesFactory.hpp"

#include <cassert>

#include "gkom/Logging.hpp"

namespace gkom {

ShapesFactory::ShapesFactory(GraphicsManager& graphicsManager)
	:	boxFactory_(graphicsManager)
	,	pyramidFactory_(graphicsManager)
	,	logger_(Logging::getLogger("ShapesFactory"))
{
	logger_("Initialized");
}

Geometry* ShapesFactory::createBox()
{
	logger_("Creating box...");

	const auto box = boxFactory_.createBox();
	assert(box != nullptr);
	return box;
}

Geometry* ShapesFactory::createPyramid()
{
	logger_("Creating pyramid...");

	const auto pyramid = pyramidFactory_.createPyramid();
	assert(pyramid != nullptr);
	return pyramid;
}

} // gkom
