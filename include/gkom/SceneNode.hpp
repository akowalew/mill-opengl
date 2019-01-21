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

	void addChildNode(SceneNode* node);

	const std::list<SceneNode*>& childNodes();

	void attachEntity(Entity* entity);

	const std::list<Entity*>& entities();

	SceneNode* parent();

private:
	std::list<SceneNode*> childNodes_;
	std::list<Entity*> entities_;
	SceneNode* parent_ {nullptr};
};

} // gkom
