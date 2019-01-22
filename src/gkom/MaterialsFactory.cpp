#include "gkom/MaterialsFactory.hpp"

#include <algorithm>

#include "gkom/ShaderLoader.hpp"
#include "gkom/ShaderProgram.hpp"
#include "gkom/Material.hpp"
#include "gkom/Logging.hpp"

namespace gkom {

MaterialsFactory::MaterialsFactory(ShaderLoader& shaderLoader)
	:	shaderLoader_(shaderLoader)
	,	logger_(Logging::getLogger("MaterialsFactory"))
{
	logger_("Initialized");
}

MaterialsFactory::~MaterialsFactory() = default;

Material
MaterialsFactory::createColorMaterial(const glm::vec3& color)
{
	logger_("Loading shader program...");
	const auto shaderProgram =
		ShaderProgram{shaderLoader_.loadShaderProgram("vertex_base",
										"fragment_base")};

	logger_("Creating material...");
	return Material{shaderProgram, color};

	// const auto material = findColorMaterial(color);
	// if(material != nullptr)
	// {
	// 	logger_("Reusing existing material...");
	// 	return *material;
	// }

	// logger_("Making new material...");
	// const auto& newMaterial = materials_.emplace_back(makeColorMaterial(color));
	// assert(newMaterial);
	// return newMaterial.get();
}

// Material*
// MaterialsFactory::findColorMaterial(const glm::vec3& color)
// {
// 	logger_("Looking for an existing material...");
// 	const auto materialsEnd = materials_.end();
// 	const auto pos = std::find_if(materials_.begin(),
// 								  materialsEnd,
// 								  [&color](const auto& material)
// 								  {
// 								  	  assert(material);
// 									  return (color == material->color);
// 								  });
// 	if(pos == materialsEnd)
// 	{
// 		return nullptr;
// 	}

// 	const auto& material = *pos;
// 	assert(material);
// 	return material.get();
// }

// std::unique_ptr<Material>
// MaterialsFactory::makeColorMaterial(const glm::vec3& color)
// {
// 	logger_("Loading shader program...");
// 	const auto shaderProgram =
// 		ShaderProgram{shaderLoader_.loadShaderProgram("vertex_base",
// 										"fragment_base")};

// 	logger_("Creating new material...");
// 	return std::make_unique<Material>(shaderProgram, color);
// }

} // gkom
