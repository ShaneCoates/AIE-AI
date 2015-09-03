#include "Particle.h"
#include "Framework.h"
#include "Texture2D.h"
#include "ParticleEngine.h"

Particle::Particle(ParticleEngine* particleEngine, unsigned int texture, Vec2 position, Vec2 velocity, float angle, float angularVelocity, Vec4 color, float size, int ttl)
{
	m_texture = texture;
    m_position = position;
    m_velocity = velocity;
    m_angle = angle;
    m_angularVelocity = angularVelocity;
    m_color = color;
    m_size = size;
    m_TTL = ttl;
}

Particle::~Particle()
{

}

void Particle::Update(float dt)
{	
	m_TTL -= dt;
    m_position += m_velocity;
	m_angle += m_angularVelocity;
}

void Particle::Draw()
{
}
