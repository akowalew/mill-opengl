#include "gkom/SceneNode.hpp"

#include <cassert>

namespace gkom {

SceneNode::SceneNode() = default;

SceneNode::SceneNode(SceneNode* parent)
{
	assert(parent != nullptr);
	parent->addChildNode(this);
}

SceneNode::~SceneNode()
{
	// Detaching of entities will be handled in Scene class
}

void SceneNode::addChildNode(SceneNode* node)
{
	assert(node != nullptr);
	assert(node->parent_ == nullptr);

	node->parent_ = this;
	childNodes_.emplace_back(node);
}

const std::list<SceneNode*>& SceneNode::childNodes()
{
	return childNodes_;
}

void SceneNode::attachEntity(Entity* entity)
{
	assert(entity != nullptr);

	entities_.emplace_back(entity);
}

const std::list<Entity*>& SceneNode::entities()
{
	return entities_;
}

SceneNode* SceneNode::parent()
{
	return parent_;
}

} // gkom
