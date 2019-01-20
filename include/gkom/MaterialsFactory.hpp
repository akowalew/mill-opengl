#pragma once

#include <memory>
#include <vector>

#include <glm/vec4.hpp>

namespace gkom {

//! Forward declarations
class Logger;
class Material;
class ShaderLoader;

class MaterialsFactory
{
public:
	MaterialsFactory(ShaderLoader& shaderLoader);

	~MaterialsFactory();

	Material* createColorMaterial(const glm::vec4& color);

	Material* findColorMaterial(const glm::vec4& color);

private:
	std::unique_ptr<Material> makeColorMaterial(const glm::vec4& color);

	ShaderLoader& shaderLoader_;

	std::vector<std::unique_ptr<Material>> colorMaterials_;

	Logger& logger_;
};

} // gkom
