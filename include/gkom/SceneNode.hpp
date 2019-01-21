#pragma once

#include <list>

namespace gkom {

class Entity;

class SceneNode
{
public:
	SceneNode();

	explicit SceneNode(SceneNode* parent);

	~SceneNode();

	void attachNode(SceneNode* node);

	const std::list<SceneNode*>& childNodes();

	void setEntity(Entity* entity);

	Entity* entity();

	SceneNode* parent();

private:
	std::list<SceneNode*> childNodes_;
	Entity* entity_ {nullptr};
	SceneNode* parent_ {nullptr};
};

} // gkom
