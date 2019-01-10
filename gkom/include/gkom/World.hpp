#pragma once

#include <vector>

#include "gkom/Shape.hpp"

namespace gkom {

class World
{
public:
	void addShape(Shape* shape);

	void removeShape(Shape* shape);

	const std::vector<Shape*> shapes() const;

private:
	std::vector<Shape*> shapes_;
};

} // gkom
