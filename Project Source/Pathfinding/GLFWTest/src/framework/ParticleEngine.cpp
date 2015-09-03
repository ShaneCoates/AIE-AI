#include "ParticleEngine.h"
#include "Framework.h"
#include "SpriteBatch_NonImmediate.h"
#include "Utils.h"

ParticleEngine::ParticleEngine(Framework* framework, Texture2D* texture[3], SceneNode *pSceneNode, unsigned int maxParticleCount) : SceneNode(framework)
{
	m_maxParticles = maxParticleCount;
	m_sceneNode = pSceneNode;
	GetLocalTransform()->CopyFrom(pSceneNode->GetGlobalTransform());
	m_texture[0] = texture[0];
	m_texture[1] = texture[1];
	m_texture[2] = texture[2];

	// allocate buffer memory
	m_TextureVertBuffer[0] = new ParticleBufferVertex[maxParticleCount]();
	m_TextureVertBuffer[1] = new ParticleBufferVertex[maxParticleCount]();
	m_TextureVertBuffer[2] = new ParticleBufferVertex[maxParticleCount]();

	m_size = 1.0f;
	m_position = Vec2();
	m_velocity = Vec2();
	m_maxVelocity = 1.0f;
	m_maxAngularVelocity = 1.0f;
	m_maxColours = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_maxLife = 40;

	m_xFlipped = true;
	m_yFlipped = false;

	m_creationRate = 10;


	// get shader 
	m_shader = reinterpret_cast<SpriteBatch_NonImmediate*>(m_Framework->GetSpriteBatch())->GetShaderProgram();

	//Generate buffers for openGL to store data on the graphics card
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	//Bind the buffers to the appropriate type.
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	// enable attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// set attribute pointers
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VertexUVColor), (void *) 0);  // Vec4 pos
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexUVColor), (void *) 16); // Vec2 uv
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexUVColor), (void *) 24); // Vec4 color

	glBindVertexArray(0);
	
}

ParticleEngine::~ParticleEngine()
{
	for(auto itr = m_particles.begin(); itr != m_particles.end(); ++itr)
    {
      	delete *itr;
		itr = m_particles.erase(itr);
    }

	glDeleteProgram(m_shader);

	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
}

void ParticleEngine::Update(float dt)
{
	for(auto itr = m_particles.begin(); itr != m_particles.end();)
    {
        if ((*itr)->GetTTL() <= 0.0f)
        {			
			delete *itr;
			itr = m_particles.erase(itr);
			continue;
		}        
		(*itr)->Update(dt);
		itr++;
    }
}

void ParticleEngine::Draw()
{
	if(m_particles.size() > 0)
	{
		unsigned int textureBufferItemCounts[3]  = { 0, 0, 0 };

		// build particle buffer
		for(auto itr = m_particles.begin(); itr != m_particles.end(); itr++)
		{
			Mat3x3 transform;

			auto particle = *itr;
			if(particle != NULL) 
			{

				transform.SetTranslation(particle->GetPosition());
				transform.SetScale(particle->GetSize(), particle->GetSize());
				transform.Rotate(particle->GetAngle());	
			
				Vec3 position = transform * Vec3(0.0f, 0.0f, 1.0f);
				Vec2 smallPos = Vec2(position.x, position.y);

				auto textureNumber = particle->GetTexture();
				auto texture = m_texture[textureNumber];

				// build quad
				float width = texture->GetWidth();
				float height = texture->GetHeight();

				Vec2 m_topLeft			= Vec2(-width/2.0f, -height/2.0f) * transform;
				Vec2 m_bottomLeft		= Vec2(-width/2.0f, height/2.0f) * transform;
				Vec2 m_bottomRight		= Vec2(width/2.0f,	 height/2.0f) * transform;
				Vec2 m_topRight			= Vec2(width/2.0f,	-height/2.0f) * transform;

				ParticleBufferVertex verts[4] = 
				{
					ParticleBufferVertex(m_topLeft,		Vec2(0.0f, 0.0f), particle->GetColor()),
					ParticleBufferVertex(m_bottomLeft,	Vec2(0.0f, 1.0f), particle->GetColor()),
					ParticleBufferVertex(m_bottomRight,	Vec2(1.0f, 1.0f), particle->GetColor()),
					ParticleBufferVertex(m_topRight,	Vec2(1.0f, 0.0f), particle->GetColor()),
				};

				// laziness
				for(int i = 0; i < 4; i++)
				{
					m_TextureVertBuffer[textureNumber][textureBufferItemCounts[textureNumber]] = verts[i];
					textureBufferItemCounts[textureNumber]++;
				}
			}
		}


		// setup shader
		glUseProgram(m_shader);
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		// generate projection matrix
		auto projection = Mat4x4::CreateOrthographic(0.0f, (float)m_Framework->GetWindowWidth(), 0.0f, (float)m_Framework->GetWindowHeight(), -1.0f, 1.0f);

		// assign to projection uniform
		glUniformMatrix4fv(glGetUniformLocation(m_shader, "projection"), 1, false, projection.m);

		// draw for each texture
		for(int i = 0; i < 3; i++)
		{
			if(textureBufferItemCounts[i] > 0) 
			{
				glActiveTexture(GL_TEXTURE0 + 0);
				glBindTexture(GL_TEXTURE_2D, m_texture[i]->GetTextureHandle());
	
				glUniform1i(glGetUniformLocation(m_shader, "texture"), 0);

				
				glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleBufferVertex) * textureBufferItemCounts[i], m_TextureVertBuffer[i], GL_STATIC_DRAW);

				glDrawArrays(GL_QUADS, 0, textureBufferItemCounts[i]);
			}
		}

		glBindVertexArray(0);
		glUseProgram(0);
	}
}

Particle* ParticleEngine::GenerateNewParticle()
{
	int textureNumber = rand() % 3;

	float rot = GetGlobalTransform().GetRightRotation();

	rot += rand() % (int)((m_maxAngle * 2000) - (m_maxAngle * 1000)) * 0.001f;

	Vec2 dir = Vec2(cosf(rot), -sinf(rot));
	if(dir.Length() > m_maxVelocity)
		dir.Normalise() * m_maxVelocity;


	m_position.x			= GetGlobalTransform().GetTranslation().x + (rand() % ((int)m_size.x) * 2.0f) - m_size.x;
	m_position.y			= GetGlobalTransform().GetTranslation().y + (rand() % ((int)m_size.y) * 2.0f) - m_size.y;

	float angle				= 0;
	float angularVelocity	= (rand() % 200 - 100) * 0.01f * m_maxAngularVelocity;
	
	Vec4 color				= Vec4(	(rand() % (int)(100 * (m_maxColours.r)) * 0.01f),
									(rand() % (int)(100 * (m_maxColours.g)) * 0.01f),
									(rand() % (int)(100 * (m_maxColours.b)) * 0.01f), 
									(rand() % (int)(100 * (m_maxColours.a)) * 0.01f));

	float size				= rand() % m_maxParticleSize * 0.01f;
    
	float ttl				= Utils::RandomNumber(1.0f, m_maxLife);
 
	return new Particle(this, textureNumber, m_position, dir, angle, angularVelocity, color, size, ttl);
}

void ParticleEngine::AddParticles()
{
    for (int i = 0; i < m_creationRate; i++)
    {
		if(m_particles.size() < m_maxParticles) 
		{
			m_particles.push_back(GenerateNewParticle());
		}
    }
}
