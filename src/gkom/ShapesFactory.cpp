#include "gkom/ShapesFactory.hpp"

#include <cassert>

#include "gkom/Logging.hpp"
#include "gkom/Geometry.hpp"

namespace gkom {

ShapesFactory::ShapesFactory(World& world, GeometryManager& geometryManager)
	:	boxFactory_(world, geometryManager)
	,	pyramidFactory_(world, geometryManager)
	,	coneFactory_(world, geometryManager)
	,	prismFactory_(world, geometryManager)
	,	logger_(Logging::getLogger("ShapesFactory"))
{
	logger_("Initialized");
}

Entity* ShapesFactory::createBox()
{
	logger_("Creating box...");
	return boxFactory_.createBox();
}

Entity* ShapesFactory::createPyramid()
{
	logger_("Creating pyramid...");

	const auto pyramid = pyramidFactory_.createPyramid();
	assert(pyramid != nullptr);
	return pyramid;
}

Entity* ShapesFactory::createCone(int sides)
{
	logger_("Creating pyramid...");

	const auto cone = coneFactory_.createCone(sides);
	assert(cone != nullptr);
	return cone;
}

Entity* ShapesFactory::createPrism(int sides)
{
	logger_("Creating prism...");

	const auto prism = prismFactory_.createPrism(sides);
	assert(prism != nullptr);
	return prism;
}

} // gkom
