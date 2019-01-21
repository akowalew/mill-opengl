#pragma once

#include <vector>
#include <optional>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace gkom {

// TODO: inherit from these ones!

using Index = unsigned int;
using Position = glm::vec3;
using Normal = glm::vec3;
using Texcoord = glm::vec2;

struct Mesh
{
	Mesh(std::vector<Position> positions,
		 std::optional<std::vector<Index>> indices = {},
		 std::optional<std::vector<Normal>> normals = {},
		 std::optional<std::vector<Texcoord>> texcoords = {})
		:	positions(std::move(positions))
		,	indices(std::move(indices))
		,	normals(std::move(normals))
		,	texcoords(std::move(texcoords))
	{}

	std::vector<Position> positions;
	std::optional<std::vector<Index>> indices;
	std::optional<std::vector<Normal>> normals;
	std::optional<std::vector<Texcoord>> texcoords;
};

} // gkom
