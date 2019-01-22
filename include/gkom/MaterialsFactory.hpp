#pragma once

#include <vector>
#include <memory>

#include <glm/vec3.hpp>

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

	Material createColorMaterial(const glm::vec3& color);

private:
	// Material* findColorMaterial(const glm::vec3& color);

	// std::unique_ptr<Material> makeColorMaterial(const glm::vec3& color);

	ShaderLoader& shaderLoader_;
	Logger& logger_;
};

} // gkom
