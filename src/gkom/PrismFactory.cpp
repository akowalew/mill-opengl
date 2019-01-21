// #include "gkom/PrismFactory.hpp"

// #include <cassert>

// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/gtx/rotate_vector.hpp>
// #include <glm/trigonometric.hpp>

// #include "gkom/GraphicsManager.hpp"
// #include "gkom/Geometry.hpp"
// #include "gkom/Logging.hpp"

// namespace gkom {

// 	PrismFactory::PrismFactory(GraphicsManager& graphicsManager)
// 		: graphicsManager_(graphicsManager)
// 		, logger_(Logging::getLogger("PrismFactory"))
// 	{
// 		logger_("Initialized");
// 	}

// 	PrismFactory::~PrismFactory() = default;

// 	Geometry* PrismFactory::createPrism(int sides)
// 	{
// 		assert(sides >= 3); // At least triangle

// 		logger_("Looking for an existing cone geometry...");
// 		const auto prism = findPrism(sides);
// 		if (prism != nullptr)
// 		{
// 			return prism;
// 		}

// 		logger_("Creating a new cone geometry...");
// 		const auto newPrismPos =
// 			prisms_.emplace_hint(prisms_.end(),
// 				std::make_pair(sides, makePrism(sides)));
// 		auto& newPrism = newPrismPos->second;
// 		return &newPrism;
// 	}

// 	Geometry* PrismFactory::findPrism(int sides)
// 	{
// 		const auto prismPos = prisms_.find(sides);
// 		if (prismPos == prisms_.end())
// 		{
// 			return nullptr;
// 		}

// 		return &(prismPos->second);
// 	}

// 	Geometry PrismFactory::makePrism(int sides)
// 	{
// 		assert(sides >= 3); // At least triangle

// 		// Generate vertices
// 		const auto angle = glm::radians(360.0f / sides);
// 		const auto corner = Vertex{ {0.0f, 0.5f, 0.0f} };
// 		auto corner2 = glm::vec3{ 0.0f, -0.5f, 0.0f };
// 		auto vertices = Vertices{ corner };
// 		vertices.emplace_back(Vertex{ corner2 });

// 		auto point2 = glm::vec3{ -0.5f, -0.5f, 0.5f };
// 		auto point = glm::vec3{ -0.5f, 0.5f, 0.5f };
// 		for (auto i = 0; i < sides; ++i)
// 		{
// 			vertices.emplace_back(Vertex{ point });
// 			vertices.emplace_back(Vertex{ point2 });
// 			point = glm::rotateY(point, angle);
// 			point2 = glm::rotateY(point2, angle);
// 		}

// 		// Generate indices
// 		auto indices = Indices{};
// 		for (unsigned int i = 2; i < sides * 2; i += 2)
// 		{
// 			// Insert next triangles
// 			indices.insert(indices.end(), { i, i + 1, i + 2 });
// 			indices.insert(indices.end(), { i + 1, i + 2, i + 3 });
// 		}

// 		// Insert last triangles
// 		indices.insert(indices.end(), { static_cast<unsigned int>(sides) * 2, static_cast<unsigned int>(sides) * 2 + 1, 2 });
// 		indices.insert(indices.end(), { static_cast<unsigned int>(sides) * 2 + 1, 2, 3 });

// 		for (unsigned int i = 1; i < sides; i++)
// 		{
// 			// Insert next triangles
// 			indices.insert(indices.end(), { i * 2, 0, i * 2 + 2 });
// 		}
// 		indices.insert(indices.end(), { static_cast<unsigned int>(sides) * 2, 0, 2 });

// 		for (unsigned int i = 1; i < sides; i++)
// 		{
// 			// Insert next triangles
// 			indices.insert(indices.end(), { i * 2 + 1, 1, i * 2 + 3 });
// 		}
// 		indices.insert(indices.end(), { static_cast<unsigned int>(sides) * 2 + 1, 1, 3 });

// 		const auto vertexArray = graphicsManager_.createVertexArray(vertices,
// 			indices);
// 		const auto indicesCount = static_cast<int>(indices.size());
// 		return Geometry{ vertexArray, indicesCount };
// 	}

// } // gkom
