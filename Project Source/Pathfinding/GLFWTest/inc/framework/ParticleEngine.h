/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Base Particle Engine class 
						Emits particles
-----------------------------------------------------------------------------*/

#ifndef PARTICLE_ENGINE_H
#define	PARTICLE_ENGINE_H

class Framework;
#include "framework\Framework.h"
#include "framework\Texture2D.h"
#include "SpriteSceneNode.h"
#include "Particle.h"
#include <list>
#include <map>


class ParticleEngine : public SceneNode
{
public:
	struct ParticleBufferVertex
	{
		ParticleBufferVertex() 
		{
			x = y = z = w = u = v = r = g = b = a = 0.0f;
		}

		ParticleBufferVertex(Vec2 position, Vec2 uv, Vec4 color)
		{
			x = position.x;
			y = position.y;
			z = 0.0f;
			w = 1.0f;

			u = uv.x;
			v = uv.y;

			r = color.r;
			g = color.g;
			b = color.b;
			a = color.a;
		}


		float x, y, z, w, u, v, r, g, b, a;
	};


	ParticleEngine(Framework* framework, Texture2D* texture[3], SceneNode* pSceneNode, unsigned int maxParticleCount);

	virtual ~ParticleEngine();

	virtual void Update(float dt);
	virtual void Draw();

	//getters and setters
	Vec2 GetSize()										{return m_size;}
	void SetSize(Vec2 size)						{m_size = size;}

	float GetMaxVelocity()								{return m_maxVelocity;}
	void SetMaxVelocity(float velocity)					{m_maxVelocity = velocity;}
	
	float GetMaxAngle()									{return m_maxAngle;}
	void SetMaxAngle(float angle)						{m_maxAngle = angle;}

	float GetMaxAngularVelocity()						{return m_maxAngularVelocity;}
	void SetMaxAngularVelocity(float velocity)			{m_maxAngularVelocity = velocity;}

	Vec4 GetMaxColours()								{return m_maxColours;}
	void SetMaxColours(Vec4 colours)				{m_maxColours = colours;}
	
	float GetMaxLife()									{return m_maxLife;}
	void SetMaxLife(float maxLife)						{m_maxLife = maxLife;}

	unsigned int GetCreationRate()						{return m_creationRate;}
	void SetCreationRate(unsigned int rate)				{m_creationRate = rate;}

	unsigned int GetMaxParticleSize()					{return m_maxParticleSize;}
	void SetMaxParticleSize(float size)					{m_maxParticleSize = size;}

	bool GetXFlipped()									{return m_xFlipped;}
	void SetXFlipped(bool flipped)						{m_xFlipped = flipped;}
	
	bool GetYFlipped()									{return m_yFlipped;}
	void SetYFlipped(bool flipped)						{m_yFlipped = flipped;}

	void AddParticles();

protected:
private:
	float random;


	SceneNode* m_sceneNode;
	std::list<Particle *> m_particles;
	Texture2D* m_texture[3];
	Vec2 m_size;
	Vec2 m_position;
	Vec2 m_velocity;
	
	Vec4 m_maxColours;

	float m_maxAngularVelocity;
	float m_maxVelocity;
	float m_maxAngle;

	float m_maxLife;
	unsigned int m_creationRate;
	unsigned int m_maxParticleSize;
	unsigned int m_maxParticles;

	bool m_xFlipped;
	bool m_yFlipped;

	Particle* GenerateNewParticle();

	GLuint m_shader;

	GLuint m_vao;
	GLuint m_vbo;

	ParticleBufferVertex* m_TextureVertBuffer[3];
};


#endif