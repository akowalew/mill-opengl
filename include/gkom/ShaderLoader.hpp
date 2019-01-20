#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <string_view>

namespace gkom {

//! Forward declarations
class GraphicsManager;
class Logger;

class ShaderLoader
{
public:
	ShaderLoader(GraphicsManager& graphicsManager);

	unsigned int loadShaderProgram(std::string_view vertexShaderName,
								   std::string_view fragmentShaderName);

private:
	unsigned int makeShaderProgram(std::string_view vertexShaderName,
								   std::string_view fragmentShaderName);

	std::string loadShaderCode(std::string_view name);

	std::string getShaderPath(std::string_view name);

	unsigned int findShaderProgram(std::string_view vertexShaderName,
								   std::string_view fragmentShaderName) const;

	std::unordered_map<
		std::string /*vertexShaderName*/,
		std::unordered_map<
			std::string /*fragmentShaderName*/,
			unsigned int /*shaderProgram*/
		>
	> shaderPrograms_;

	GraphicsManager& graphicsManager_;
	Logger& logger_;
};

} // gkom
