/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Base Physics Objects
						All entities that use physics should inherit from this
-----------------------------------------------------------------------------*/

#ifndef PHYSICS_OBJECT_H
#define	PHYSICS_OBJECT_H

#include "framework\Framework.h"
#include "framework\Texture2D.h"
#include "SpriteSceneNode.h"

class PhysicsObject : public SpriteSceneNode
{
public:

	PhysicsObject(Framework* framework, Texture2D* pTexture);

	virtual ~PhysicsObject();

	virtual void Update(float dt);
	virtual void Draw();

	void AddForce(Vec2 _target, float _force);
	void TurnTowards(Vec2 _target, float _force);
	
	Vec2 GetForce()						{return m_force;}			
	float GetAcceleration()				{return m_acceleration;}
	float GetVelocity()					{return m_velocity;}
	float GetMass()						{return m_mass;}
	float GetFriction()					{return m_friction;}
	
	void SetMass(float mass)			{m_mass = mass;}
	void SetFriction(float friction)	{m_friction = friction;}
	void SetMaxVelocity(float velocity) {m_maxVelocity = velocity;}

protected:
private:

	Vec2		m_force;
	Vec2		m_direction;

	float		m_acceleration;
	float		m_velocity;
	float		m_mass;
	float		m_friction;
	float		m_maxVelocity;


};


#endif