#pragma once

#include <memory>
#include <unordered_map>

#include "gkom/Geometry.hpp"

namespace gkom {

	//! Forward declarations
	class GraphicsManager;
	class Geometry;
	class Logger;

	class PrismFactory
	{
	public:
		PrismFactory(GraphicsManager& graphicsManager);

		~PrismFactory();

		Geometry* createPrism(int sides);

		Geometry* findPrism(int sides);

	private:
		Geometry makePrism(int sides);

		GraphicsManager& graphicsManager_;
		Logger& logger_;
		std::unordered_map<int /*sides*/, Geometry> prisms_;
	};

} // gkom