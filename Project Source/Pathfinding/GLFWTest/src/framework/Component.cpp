#include "Component.h"
#include "framework.h"
#include "Gamepad.h"
#include "ParticleEngine.h"
#include <math.h>
#include <iostream>

KeyboardController::KeyboardController(PhysicsObject *pPhysics, GLuint lKey, GLuint rKey, GLuint uKey, GLuint dKey, GLuint sKey, ParticleEngine* pParticles)
{
	m_leftKey	= lKey;
	m_rightKey	= rKey;
	m_upKey		= uKey;
	m_downKey	= dKey;
	m_shootKey  = sKey;

	m_physicsObject = pPhysics;
	m_particleEngine = pParticles;
	m_cooldown = 0.1f;
}

void KeyboardController::Update(Framework *framework, float dt,  SceneNode *pSceneNode)
{
	
	m_cooldown -= dt;

	auto pPlayer = reinterpret_cast<Player *>(pSceneNode);

	if(framework->GetKeyDown(m_upKey	) ) m_physicsObject->AddForce(Vec2(0, 1.0f));
	if(framework->GetKeyDown(m_downKey	) ) m_physicsObject->AddForce(Vec2(0, -1.0f));

	if(framework->GetKeyDown(m_leftKey  ) ) m_physicsObject->AddForce(Vec2(1.0f, 0));
	if(framework->GetKeyDown(m_rightKey	) ) m_physicsObject->AddForce(Vec2(-1.0f, 0));
	if(framework->GetKeyDown(m_shootKey	) && m_cooldown <= 0.0f ) 
		{
			m_cooldown = 0.1f;
		}

	if(m_particleEngine != nullptr)
	{
		if(framework->GetKeyDown(m_upKey))
			m_particleEngine->AddParticles();
	}
}

GamepadController::GamepadController(PhysicsObject *pPhysics, Gamepad *pGamepad)
{
	m_gamepad = pGamepad;

	m_physicsObject = pPhysics;
}

void GamepadController::Update(Framework *framework, float dt, SceneNode *pSceneNode)
{
	
	auto pPlayer = reinterpret_cast<Player *>(pSceneNode);

	m_gamepad->Update();

	if (!m_gamepad->LStick_InDeadzone())
	{
	}
	if (!m_gamepad->LStick_InDeadzone())
	{
	}
	if (!m_gamepad->RStick_InDeadzone())
	{
	}
	if (m_gamepad->RightTrigger() > 0.0f)
	{
	}

	m_gamepad->RefreshState();
}

PhysicsObject::PhysicsObject(float mass, float friction, SceneNode *pSceneNode)
{
	m_force			= Vec2(0,0);
	m_acceleration	= Vec2(0,0);
	m_velocity		= Vec2(0,0);
	m_position		= Vec2(0,0);
	
	m_mass			= mass;
	m_friction		= friction;
	m_sceneNode = pSceneNode;
}


void PhysicsObject::Update(Framework *framework, float dt, SceneNode *pSceneNode)
{
	Vec2 fakeFriction = m_velocity * -m_friction;

	m_acceleration	= (m_force + fakeFriction) * (1.0f / m_mass);
	m_velocity		+= m_acceleration * dt;

	m_position		+= m_velocity;

	// reset the force.
	m_force.x = 0.0f;
	m_force.y = 0.0f;

	m_sceneNode->GetLocalTransform()->Translate( m_velocity );
	//m_sceneNode->GetLocalTransform()->TranslateGlobal(m_velocity);
}

void PhysicsObject::AddForce(Vec2 f)
{
	m_position = m_sceneNode->GetGlobalTransform().GetTranslation();

	m_force += f;
}