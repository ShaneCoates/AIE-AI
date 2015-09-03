/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Base Particle class 
-----------------------------------------------------------------------------*/

#ifndef PARITCLE_H
#define	PARITCLE_H


#include "framework\Framework.h"
#include "framework\Texture2D.h"
#include "SpriteSceneNode.h"
#include <list>

class ParticleEngine;

class Particle 
{
public:

	Particle(ParticleEngine* particleEngine, unsigned int texture, Vec2 position, Vec2 velocity, float angle, float angularVelocity, Vec4 color, float size, int ttl);

	virtual ~Particle();
	virtual void Update(float dt);
	virtual void Draw();

protected:
private:

	Framework* m_framework;

	unsigned int m_texture;			// The texture that will be drawn to represent the particle
	Vec2 m_position;				// The current position of the particle        
	Vec2 m_velocity;				// The speed of the particle at the current instance
	Vec4 m_color;					// The color of the particle

	float m_angle;					// The current angle of rotation of the particle
	float m_angularVelocity;		// The speed that the angle is changing
	float m_size;					// The size of the particle
	float m_TTL;					// The 'time to live' of the particle

public:

	//Getters and Setters
	unsigned int GetTexture()					{return m_texture;}
	Vec2 GetPosition()						{return m_position;}		
	Vec2 GetVelocity()						{return m_velocity;}		
	float GetAngle()							{return m_angle;}	
	float GetAngularVelocity()					{return m_angularVelocity;}
	Vec4 GetColor()						{return m_color;}
	float GetSize()								{return m_size;}			
	float GetTTL()								{return m_TTL;}

	void SetTexture			(unsigned int texture	)		{m_texture = texture;}
	void SetPosition		(Vec2 position		)		{m_position = position;}	
	void SetVelocity		(Vec2 velocity		)		{m_velocity = velocity;}
	void SetAngle			(float angle			)		{m_angle = angle;}
	void SetAngularVelocity	(float angularVelocity	)		{m_angularVelocity = angularVelocity;}
	void SetColor			(Vec4 color		)		{m_color = color;}
	void SetTTL				(float TTL				)		{m_TTL = TTL;}

};


#endif