#include "gkom/Scene.hpp"

#include <cassert>

#include "gkom/Logging.hpp"

namespace gkom {

Scene::Scene()
	:	rootNode_()
	,	logger_(Logging::getLogger("Scene"))
{
	logger_("Initialized");
}

Scene::~Scene() = default;

SceneNode* Scene::createNode(SceneNode* parent)
{
	logger_("Creating new node...");
	auto& node = nodes_.emplace_back(makeNode(parent));
	assert(node != nullptr);
	return node.get();
}

SceneNode* Scene::rootNode()
{
	return &rootNode_;
}

std::unique_ptr<SceneNode> Scene::makeNode(SceneNode* parent)
{
	return std::make_unique<SceneNode>((parent != nullptr) ? parent : &rootNode_);
}

} // gkom
