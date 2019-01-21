#include "gkom/ShapesFactory.hpp"

#include <cassert>

#include "gkom/Logging.hpp"

namespace gkom {

ShapesFactory::ShapesFactory()
	:	boxFactory_()
	// ,	pyramidFactory_()
	// ,	coneFactory_()
	// ,	prismFactory_()
	,	logger_(Logging::getLogger("ShapesFactory"))
{
	logger_("Initialized");
}

Mesh* ShapesFactory::createBox()
{
	logger_("Creating box...");

	const auto box = boxFactory_.createBox();
	assert(box != nullptr);
	return box;
}

Mesh* ShapesFactory::createBoxWithNormals()
{
	logger_("Creating box with normals...");

	const auto boxWithNormals = boxFactory_.createBoxWithNormals();
	assert(boxWithNormals != nullptr);
	return boxWithNormals;
}


// Mesh* ShapesFactory::createPyramid()
// {
// 	logger_("Creating pyramid...");

// 	const auto pyramid = pyramidFactory_.createPyramid();
// 	assert(pyramid != nullptr);
// 	return pyramid;
// }

// Mesh* ShapesFactory::createCone(int sides)
// {
// 	logger_("Creating pyramid...");

// 	const auto cone = coneFactory_.createCone(sides);
// 	assert(cone != nullptr);
// 	return cone;
// }

// Mesh* ShapesFactory::createPrism(int sides)
// {
// 	logger_("Creating prism...");

// 	const auto prism = prismFactory_.createPrism(sides);
// 	assert(prism != nullptr);
// 	return prism;
// }

} // gkom
