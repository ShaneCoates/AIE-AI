#include "SpriteBatch_Immediate.h"
#include "Texture2D.h"
#include "GLFW/glfw3.h"
#include "Game.h"
#include "Framework.h"

SpriteBatch_Immediate::SpriteBatch_Immediate(Framework *pFramework) : SpriteBatch(pFramework)
{
	m_pFramework = pFramework;
}

void SpriteBatch_Immediate::Begin()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION); // DEPRECIATED: shaders used instead - user to provide projection matrix to the shader
	glLoadIdentity();			 // sets the GL_PROJECTION matrix to the identity matrix

	// setup orthographic projection (for rendering 2D)
	// DEPRECIATED: the projection matrix would be sent to the active shader
		glOrtho(0.0f, m_pFramework->GetWindowWidth(), m_pFramework->GetWindowHeight(), 0, -1, 1);		// WINDOW ORIGIN: Top Left
	//	glOrtho(0.0f, windowWidth, 0, windowHeight, -1, 1);		// WINDOW ORIGIN: Bottom Left
		
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		

	// DEPRECIATED: pixel shaders define the final color after rasterization step in the graphics pipeline
	glEnable(GL_TEXTURE_2D); 

	// DEPRECIATED: again, Matrices do not exist on future versions of OpenGL.
	// a model view matrix would be sent to the shader... 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SpriteBatch_Immediate::End()
{

}

void SpriteBatch_Immediate::DrawSprite(Texture2D* pTexture, const Vec2& position, bool centered)
{
	Texture2D* m_texture		= pTexture;
	unsigned int width			= m_texture->GetWidth();
	unsigned int height			= m_texture->GetHeight();

	Vec3 m_position				= Vec3(position.x, position.y, 1.0f);

	Vec3 m_topLeft				= Vec3(position.x - width/ 2, position.y - height / 2, 1.0f);
	Vec3 m_bottomLeft			= Vec3(position.x - width/ 2, position.y + height / 2, 1.0f);
	Vec3 m_bottomRight			= Vec3(position.x + width/ 2, position.y + height / 2, 1.0f);
	Vec3 m_topRight				= Vec3(position.x + width/ 2, position.y - height / 2, 1.0f);

	if(centered)
	{
		Vec3 m_topLeft			= Vec3(position.x,			position.y,			 1.0f);
		Vec3 m_bottomLeft		= Vec3(position.x,			position.y + height, 1.0f);
		Vec3 m_bottomRight		= Vec3(position.x + width, position.y + height, 1.0f);
		Vec3 m_topRight			= Vec3(position.x + width, position.y,			 1.0f);
	}

	// bind the texture that we wish to use for rendering
	glBindTexture( GL_TEXTURE_2D, m_texture->GetTextureHandle() );

	glBegin(GL_QUADS);

		glColor4f(m_red, m_green, m_blue, m_alpha);		
		
		// Top Left Of The Texture and Quad:
		glTexCoord2f(m_left, m_top); 
		glVertex3f(m_topLeft.x,		m_topLeft.y,		m_topLeft.z);
	
		// Bottom Left Of The Texture and Quad:
		glTexCoord2f(m_left, m_bottom); 
		glVertex3f(m_bottomLeft.x,	m_bottomLeft.y,		m_bottomLeft.z);	

		// Bottom Right Of The Texture and Quad:
		glTexCoord2f(m_right, m_bottom); 
		glVertex3f(m_bottomRight.x, m_bottomRight.y,	m_bottomRight.z);  
			
		// Top Right Of The Texture and Quad:
		glTexCoord2f(m_right, m_top); 
		glVertex3f(m_topRight.x,	m_topRight.y,		m_topRight.z);   

	glEnd();
}

void SpriteBatch_Immediate::DrawSprite(Texture2D* pTexture, const Mat3x3& transform, bool centered)
{
	int m_width = pTexture->GetWidth();
	int m_height = pTexture->GetHeight();

	Vec3 m_topLeft			= Vec3(-m_width/2.0f,	-m_height/2.0f, 1.0f) * transform;
	Vec3 m_bottomLeft		= Vec3(-m_width/2.0f,	 m_height/2.0f, 1.0f) * transform;
	Vec3 m_bottomRight		= Vec3(m_width/2.0f,	 m_height/2.0f, 1.0f) * transform;
	Vec3 m_topRight		= Vec3(m_width/2.0f,	-m_height/2.0f, 1.0f) * transform;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureHandle());
	glBegin(GL_QUADS);

	glColor4f(m_red, m_green, m_blue, m_alpha);		
	
	// Top Left Of The Texture and Quad:
	glTexCoord2f(m_left, m_top); 
	glVertex3f(m_topLeft.x,		m_topLeft.y,		m_topLeft.z);
	
	// Bottom Left Of The Texture and Quad:
	glTexCoord2f(m_left, m_bottom); 
	glVertex3f(m_bottomLeft.x,	m_bottomLeft.y,		m_bottomLeft.z);	

	// Bottom Right Of The Texture and Quad:
	glTexCoord2f(m_right, m_bottom); 
	glVertex3f(m_bottomRight.x, m_bottomRight.y,	m_bottomRight.z);  
			
	// Top Right Of The Texture and Quad:
	glTexCoord2f(m_right, m_top); 
	glVertex3f(m_topRight.x,	m_topRight.y,		m_topRight.z);  


	glEnd();

	glDisable(GL_BLEND);
}

void SpriteBatch_Immediate::DrawSprite(Texture2D* pTexture, const Vec2& scale, const Mat3x3& transform, bool centered, Vec4 UV)
{

	SetUVCoords(UV);

	int m_width = scale.x;
	int m_height = scale.y;

	Vec3 m_topLeft			= Vec3(-m_width/2.0f,	-m_height/2.0f, 1.0f) * transform;
	Vec3 m_bottomLeft		= Vec3(-m_width/2.0f,	 m_height/2.0f, 1.0f) * transform;
	Vec3 m_bottomRight		= Vec3(m_width/2.0f,	 m_height/2.0f, 1.0f) * transform;
	Vec3 m_topRight			= Vec3(m_width/2.0f,	-m_height/2.0f, 1.0f) * transform;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureHandle());
	glBegin(GL_QUADS);

	glColor4f(m_red, m_green, m_blue, m_alpha);		
	
	// Top Left Of The Texture and Quad:
	glTexCoord2f(m_left, m_top); 
	glVertex3f(m_topLeft.x,		m_topLeft.y,		m_topLeft.z);
	
	// Bottom Left Of The Texture and Quad:
	glTexCoord2f(m_left, m_bottom); 
	glVertex3f(m_bottomLeft.x,	m_bottomLeft.y,		m_bottomLeft.z);	

	// Bottom Right Of The Texture and Quad:
	glTexCoord2f(m_right, m_bottom); 
	glVertex3f(m_bottomRight.x, m_bottomRight.y,	m_bottomRight.z);  
			
	// Top Right Of The Texture and Quad:
	glTexCoord2f(m_right, m_top); 
	glVertex3f(m_topRight.x,	m_topRight.y,		m_topRight.z);  


	glEnd();

	glDisable(GL_BLEND);
	SetUVCoords(Vec4(0.0f,	1.0f, 0.0f, 1.0f));

}