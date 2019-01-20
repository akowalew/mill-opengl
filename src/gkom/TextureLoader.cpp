#include "gkom/TextureLoader.hpp"

#include <SOIL.h>

#include "gkom/GraphicsManager.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

TextureLoader::TextureLoader(GraphicsManager& gfxManager)
	:	gfxManager_(gfxManager)
	,	logger_(Logging::getLogger("TextureLoader"))
{
	logger_("Inititalized");
}

unsigned int TextureLoader::loadTexture(const std::string& name)
{
	const auto texture = findTexture(name);
	if(texture != 0)
	{
		return texture;
	}

	const auto newTexture = makeTexture(name);
	assert(newTexture != 0);
	textures_[name.data()] = texture;
	return newTexture;
}

unsigned int TextureLoader::findTexture(std::string_view name) const
{
	auto pos = textures_.find(name.data());
	if(pos != textures_.end())
	{
		return 0;
	}

	const auto texture = pos->second;
	assert(texture != 0);
	return texture;
}

unsigned int TextureLoader::makeTexture(std::string_view name)
{
	using Image = std::unique_ptr<unsigned char>;

	const auto path = getTexturePath(name);
	int width, height, channels;
	auto image = Image(SOIL_load_image(path.data(), &width, &height,
									   &channels, SOIL_LOAD_RGB));
	if(!image)
	{
		throw std::runtime_error("Could not load 2D texture from file");
	}

	const auto levelOfDetail = 9;
	const auto texture =
		gfxManager_.createTexture(levelOfDetail, width, height, image.get());
	assert(texture != 0);
	return texture;
}

std::string TextureLoader::getTexturePath(std::string_view name)
{
	return (std::string("res/") + name.data() + ".png");
}

} // gkom
