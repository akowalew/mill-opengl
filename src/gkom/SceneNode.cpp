#include "gkom/SceneNode.hpp"

#include <cassert>

namespace gkom {

SceneNode::SceneNode() = default;

SceneNode::SceneNode(SceneNode* parent)
{
	assert(parent != nullptr);
	parent->attachNode(this);
}

SceneNode::~SceneNode() = default;

void SceneNode::attachNode(SceneNode* node)
{
	assert(node != nullptr);

	const auto parent = node->parent_;
	if(parent != nullptr)
	{
		// Detach node from parent
		parent->childNodes_.remove(node);
	}

	node->parent_ = this;
	childNodes_.emplace_back(node);
}

const std::list<SceneNode*>& SceneNode::childNodes()
{
	return childNodes_;
}

void SceneNode::setEntity(Entity* entity)
{
	entity_ = entity;
}

Entity* SceneNode::entity()
{
	return entity_;
}

SceneNode* SceneNode::parent()
{
	return parent_;
}

} // gkom
