#pragma once

#include <vector>
#include <memory>

#include <glm/vec3.hpp>

namespace gkom {

// Forward declarations
struct Color;
class Logger;

class ColorFactory
{
public:
	ColorFactory();

	~ColorFactory();

	Color* createColor();

	Color* createColor(const glm::vec3& col);

private:
	std::vector<std::unique_ptr<Color>> colors_;
	Logger& logger_;
};

} // gkom
