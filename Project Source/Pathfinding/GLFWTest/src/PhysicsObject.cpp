#include "PhysicsObject.h"
#include "Framework.h"


PhysicsObject::PhysicsObject(Framework* framework, Texture2D* pTexture) : SpriteSceneNode(framework, pTexture)
{
	m_Framework = framework;

	m_force			= Vec2(0,0);
	m_acceleration	= 0;
	m_velocity		= 0;

	m_mass			= 1.0f;
	m_friction		= 1.0f;
	m_maxVelocity	= 1.0f;
	m_direction		= Vec2(0, 1);
}

PhysicsObject::~PhysicsObject()
{

}

void PhysicsObject::Update(float dt)
{	
	m_velocity		+= m_acceleration * dt;
	
	if(m_velocity > m_maxVelocity)
		m_velocity = m_maxVelocity;

	float fakeFriction = m_velocity * -m_friction;
	m_acceleration = fakeFriction * (1.0f / m_mass);
	
	GetLocalTransform()->Translate( m_direction * m_velocity );
}

void PhysicsObject::Draw()
{
	SpriteSceneNode::Draw();
}

void PhysicsObject::AddForce(Vec2 _towards, float _force)
{
	m_direction = _towards;
	float fakeFriction = m_velocity * -m_friction;
	m_acceleration = (_force + fakeFriction) * (1.0f / m_mass);
}


void PhysicsObject::TurnTowards(Vec2 _target, float _force)
{
	Vec2 headingPos;
	headingPos.x = GetLocalTransform()->GetTranslation().x;
	headingPos.y = GetLocalTransform()->GetTranslation().y;

	Vec2 targetForce = (_target - headingPos).Normalise();

	float _targetRad = atan2(targetForce.x, targetForce.y);
	float rot = GetLocalTransform()->GetUpRotation();

	if(_targetRad - rot > M_PI)
		_targetRad -= 2 * M_PI;
	if(rot - _targetRad > M_PI)
		rot -= 2 * M_PI;

	float distance = (_target - headingPos).Length();

	if(_targetRad > rot + (m_velocity * 0.01f))
		GetLocalTransform()->Rotate((M_PI / distance));
	if(_targetRad < rot - (m_velocity * 0.01f))						  
		GetLocalTransform()->Rotate(-(M_PI / distance));

	AddForce( Vec2(0, 1), _force );
}