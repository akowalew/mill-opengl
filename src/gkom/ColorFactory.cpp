#include "gkom/ColorFactory.hpp"

#include <cassert>

#include "gkom/Color.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

ColorFactory::ColorFactory()
	:	logger_(Logging::getLogger("ColorFactory"))
{
	logger_("Initialized");
}

ColorFactory::~ColorFactory() = default;

Color* ColorFactory::createColor()
{
	const auto& color = colors_.emplace_back(std::make_unique<Color>());
	assert(color);
	return color.get();
}

Color* ColorFactory::createColor(const glm::vec3 &col)
{
	const auto& color = colors_.emplace_back(std::make_unique<Color>(col));
	assert(color);
	return color.get();
}

} // gkom
