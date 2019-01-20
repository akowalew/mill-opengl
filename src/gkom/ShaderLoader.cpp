#include "gkom/ShaderLoader.hpp"

#include <fstream>
#include <sstream>

#include "gkom/GraphicsManager.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

ShaderLoader::ShaderLoader(GraphicsManager& graphicsManager)
	:	graphicsManager_(graphicsManager)
	,	logger_(Logging::getLogger("ShaderLoader"))
{
	logger_("Initialized");
}

unsigned int
ShaderLoader::loadShaderProgram(std::string_view vshName,
							    std::string_view fshName)
{
	const auto shaderProgram = findShaderProgram(vshName, fshName);
	if(shaderProgram != 0)
	{
		return shaderProgram;
	}

	const auto newShaderProgram = makeShaderProgram(vshName, fshName);
	assert(newShaderProgram != 0);
	shaderPrograms_[vshName.data()][fshName.data()] = newShaderProgram;
	return newShaderProgram;
}

unsigned int
ShaderLoader::makeShaderProgram(std::string_view vshName,
							    std::string_view fshName)
{
	logger_("Loading vertex shader code...");
	const auto vshCode = loadShaderCode(vshName);

	logger_("Loading fragment shader code...");
	const auto fshCode = loadShaderCode(fshName);

	logger_("Creating shader program...");
	return graphicsManager_.createShaderProgram(vshCode, fshCode);
}

std::string
ShaderLoader::loadShaderCode(std::string_view name)
{
	using namespace std::string_literals;

	logger_("Opening shader file...");
	const auto path = getShaderPath(name);
	auto ifs = std::ifstream{};
	ifs.open(path);
	if(!ifs)
	{
		throw std::runtime_error("Could not open shader code file: "s
								 + name.data());
	}

	logger_("Reading shader file...");
	auto ss = std::stringstream{};
	ss << ifs.rdbuf();
	if(!ss)
	{
		throw std::runtime_error("Could not read shader code file: "s
								 + name.data());
	}

	return ss.str();
}

std::string
ShaderLoader::getShaderPath(std::string_view name)
{
	return (std::string("res/") + name.data() + ".glsl");
}

unsigned int
ShaderLoader::findShaderProgram(std::string_view vertexShaderName,
							    std::string_view fragmentShaderName) const
{
	const auto vshPos = shaderPrograms_.find(vertexShaderName.data());
	if(vshPos == shaderPrograms_.end())
	{
		return 0;
	}

	const auto& fshsMap = vshPos->second;
	const auto fshPos = fshsMap.find(fragmentShaderName.data());
	if(fshPos == fshsMap.end())
	{
		return 0;
	}

	const auto shaderProgram = fshPos->second;
	assert(shaderProgram != 0);
	return shaderProgram;
}

} // gkom
