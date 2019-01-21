#pragma once

#include <vector>
#include <memory>

#include "gkom/SceneNode.hpp"

namespace gkom {

// Forward declarations
class Logger;
class SceneNode;

class Scene
{
public:
	Scene();

	~Scene();

	SceneNode* createNode();

	SceneNode* rootNode();

private:
	std::unique_ptr<SceneNode> makeNode();

	std::vector<std::unique_ptr<SceneNode>> nodes_;
	SceneNode rootNode_;
	Logger& logger_;
};

} // gkom
