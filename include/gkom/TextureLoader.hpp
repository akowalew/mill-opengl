#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace gkom {

//! Forward declaration
class Logger;
class GraphicsManager;

class TextureLoader
{
public:
	TextureLoader(GraphicsManager& graphicsManager);

	unsigned int loadTexture(const std::string& name);

private:
	unsigned int makeTexture(std::string_view name);

	unsigned int findTexture(std::string_view name) const;

	static std::string getTexturePath(std::string_view name);

	std::unordered_map<std::string, unsigned int> textures_;
	GraphicsManager& gfxManager_;
	Logger& logger_;
};

} // gkom
