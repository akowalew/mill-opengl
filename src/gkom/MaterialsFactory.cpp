#include "gkom/MaterialsFactory.hpp"

#include <algorithm>

#include "gkom/ShaderLoader.hpp"
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

Material*
MaterialsFactory::createColorMaterial(const glm::vec4 &color)
{
	logger_("Looking for a color material...");
	if(auto material = findColorMaterial(color); material != nullptr)
	{
		return material;
	}

	logger_("Making new color material...");
	auto& newMaterial =
		colorMaterials_.emplace_back(makeColorMaterial(color));
	assert(newMaterial);
	return newMaterial.get();
}

Material*
MaterialsFactory::findColorMaterial(const glm::vec4 &color)
{
	const auto colorMaterialsEnd = colorMaterials_.end();
	const auto pos = std::find_if(colorMaterials_.begin(),
					              colorMaterialsEnd,
					 		      [&color](const auto& material)
					 		      {
						 		      assert(material);
						 		      return (material->color == color);
					 		      });
	if(pos == colorMaterialsEnd)
	{
		logger_("Color material doesn't exist");
		return nullptr;
	}

	logger_("Color material exist");
	const auto material = pos->get();
	assert(material != nullptr);
	return material;
}

std::unique_ptr<Material>
MaterialsFactory::makeColorMaterial(const glm::vec4& color)
{
	logger_("Loading shader program...");
	const auto shaderProgram =
		shaderLoader_.loadShaderProgram("vertex_color",
										"fragment_color");

	logger_("Creating new color material...");
	return std::make_unique<Material>(color, shaderProgram);
}

} // gkom
