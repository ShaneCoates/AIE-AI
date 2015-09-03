#include "SpriteBatch.h"
#include "SpriteBatch_Immediate.h"
#include "SpriteBatch_NonImmediate.h"
#include "Framework.h"
#include <Mathlib.h>

SpriteBatch::SpriteBatch(Framework *pFramework)
{
	m_pFramework	= pFramework;
	m_red			= 1.0f;
	m_green			= 1.0f;
	m_blue			= 1.0f;
	m_alpha			= 1.0f;

	m_top			= 0.0f;
	m_bottom		= 1.0f;
	m_left			= 0.0f;
	m_right			= 1.0f;
}

SpriteBatch* SpriteBatch::Create(Framework *pFramework, ESpriteBatchType type)
{
	if(type == IMMEDIATE)
	{
		return new SpriteBatch_Immediate(pFramework);
	}
	else if (type == NON_IMMEDIATE)
	{
		return new SpriteBatch_NonImmediate(pFramework);
	}
	
	return new SpriteBatch(pFramework);
}

void SpriteBatch::Destroy( SpriteBatch* pSpriteBatch)
{
	delete pSpriteBatch;
}

void SpriteBatch::SetRenderColour(float r, float g, float b, float a)
{
	m_red = r;
	m_blue = b;
	m_green = g;
	m_alpha = a;
}

void SpriteBatch::SetUVCoords(Vec4 UV)
{
	m_top		= UV.x;	
	m_bottom	= UV.y;
	m_left		= UV.z;
	m_right		= UV.w;	
}