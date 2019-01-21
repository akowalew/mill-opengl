#pragma once

#include <vector>
#include <memory>

#include "gkom/Mesh.hpp"

namespace gkom {

//! Forward declarations
class Logger;

class BoxFactory
{
public:
	BoxFactory();

	~BoxFactory();

	// TODO: Add builder:
	// withNormals(true), statical(true), dynamical(false) etc

	Mesh* createBox(bool withNormals);

	Mesh* createBox();

	Mesh* createBoxWithNormals();

private:
	std::unique_ptr<Mesh> makeBox();

	std::unique_ptr<Mesh> makeBoxWithNormals();

	std::vector<Position> makePositions();

	std::vector<Normal> makeNormals();

	std::vector<Texcoord> makeTexcoords();

	std::unique_ptr<Mesh> box_;
	std::unique_ptr<Mesh> boxWithNormals_;
	Logger& logger_;
};

} // gkom
