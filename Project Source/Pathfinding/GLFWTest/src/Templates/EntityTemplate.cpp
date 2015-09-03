#include "Templates\EntityTemplate.h"
#include "Framework.h"


Entity::Entity(Framework* framework, Texture2D* pTexture) : SpriteSceneNode(framework, pTexture)
{
	m_Framework = framework;
}

Entity::~Entity()
{

}

void Entity::Update(float dt)
{
}

void Entity::Draw()
{
	SpriteSceneNode::Draw();
}
