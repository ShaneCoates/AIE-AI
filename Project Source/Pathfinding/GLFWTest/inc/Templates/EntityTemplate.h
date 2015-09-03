/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Base Entity class template

						All entity classes should roughly resemble
						the structure of this
-----------------------------------------------------------------------------*/

#ifndef ENTITY_H
#define	ENTITY_H

#include "framework\Framework.h"
#include "PhysicsObject.h"
class Texture2D;

class Entity : public SpriteSceneNode
{
public:

	Entity(Framework* framework, Texture2D* pTexture);

	virtual ~Entity();

	virtual void Update(float dt);
	virtual void Draw();



protected:
private:


};


#endif