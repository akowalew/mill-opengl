#include "gkom/MaterialsFactory.hpp"

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
MaterialsFactory::createMaterial()
{
	if(material_)
	{
		logger_("Reusing existing material...");
		return material_.get();
	}

	logger_("Making new material...");
	material_ = std::move(makeMaterial());
	assert(material_);
	return material_.get();
}

std::unique_ptr<Material>
MaterialsFactory::makeMaterial()
{
	logger_("Loading shader program...");
	const auto shaderProgram =
		shaderLoader_.loadShaderProgram("vertex_base",
										"fragment_base");

	logger_("Creating new material...");
	return std::make_unique<Material>(shaderProgram);
}

} // gkom
