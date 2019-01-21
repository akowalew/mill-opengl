#pragma once

#include <memory>

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

	Material* createMaterial();

private:
	std::unique_ptr<Material> makeMaterial();

	std::unique_ptr<Material> material_;
	ShaderLoader& shaderLoader_;
	Logger& logger_;
};

} // gkom
