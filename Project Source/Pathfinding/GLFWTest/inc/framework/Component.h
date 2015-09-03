#ifndef COMPONENT_H
#define	COMPONENT_H


#include "Framework.h"
#include "MathLib.h"

class Player;
class Gamepad;
class PhysicsObject;
class SceneNode;
class ParticleEngine;
class Framework;

class IComponent
{
	public:
	
		virtual void Update(Framework *framework, float dt, SceneNode *pSceneNode) = 0;
	
	protected:
	private:
};

class KeyboardController : public IComponent
{
public:

	KeyboardController(PhysicsObject *pPhysics, GLuint lKey, GLuint rKey, GLuint uKey, GLuint dKey, GLuint sKey, ParticleEngine *pParticles = nullptr);
	virtual void Update(Framework *framework, float dt, SceneNode *pSceneNode);

protected:
private:

	GLuint m_leftKey;
	GLuint m_rightKey;
	GLuint m_upKey;
	GLuint m_downKey;
	GLuint m_shootKey;

	PhysicsObject* m_physicsObject;
	ParticleEngine* m_particleEngine;

	float m_cooldown;
	
};

class GamepadController : public IComponent
{
public:

	GamepadController(PhysicsObject *pPhysics, Gamepad *pGamepad);
	virtual void Update(Framework *framework, float dt, SceneNode *pSceneNode);

protected:
private:

	Gamepad *m_gamepad;
		
	PhysicsObject* m_physicsObject;

};

class PhysicsObject : public IComponent
{
public:
		
	PhysicsObject(float mass, float friction, SceneNode *pSceneNode);

	virtual void Update(Framework *framework, float dt, SceneNode *pSceneNode);


	void AddForce(Vec2 f);

	Vec2 GetForce()					{return m_force;}			
	Vec2 GetAcceleration()			{return m_acceleration;}
	Vec2 GetVelocity()				{return m_velocity;}
	Vec2 GetPosition()				{return m_position;}
	
	float GetMass()					{return m_mass;}
	float GetFriction()				{return m_friction;}

	void SetMass(float mass)		{m_mass = mass;}
	void SetFriction(float friction){m_friction = friction;}


private:

	Vec2	m_force;
	Vec2	m_acceleration;
	Vec2	m_velocity;
	Vec2	m_position;
			
	float		m_mass;
	float		m_friction;

	SceneNode* m_sceneNode;
};

#endif



