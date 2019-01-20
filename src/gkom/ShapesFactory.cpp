#include "gkom/ShapesFactory.hpp"

#include <cassert>

#include "gkom/Logging.hpp"

namespace gkom {

ShapesFactory::ShapesFactory(GraphicsManager& graphicsManager)
	:	boxFactory_(graphicsManager)
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

} // gkom
