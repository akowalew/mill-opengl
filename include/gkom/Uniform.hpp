#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace gkom {

class Uniform
{
public:
	Uniform(int location) noexcept;

	void loadValue(float v0);

	void loadValue(float v0, float v1);

	void loadValue(float v0, float v1, float v2);

	void loadValue(float v0, float v1, float v2, float v3);

	void loadValue(const glm::vec2& v);

	void loadValue(const glm::vec3& v);

	void loadValue(const glm::vec4& v);

	void loadValue(int v0);

	void loadValue(int v0, int v1);

	void loadValue(int v0, int v1, int v2);

	void loadValue(int v0, int v1, int v2, int v3);

	void loadValue(unsigned int v0);

	void loadValue(unsigned int v0, unsigned int v1);

	void loadValue(unsigned int v0, unsigned int v1, unsigned int v2);

	void loadValue(unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);

	void loadMatrix(const glm::mat3& v);

	void loadMatrix(const glm::mat4& v);

	operator int() const noexcept;

private:
	int location_;
};

} // gkom
