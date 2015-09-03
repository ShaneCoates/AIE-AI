/*---------------------------------------------------------------------------*/
/*																			 */	
/*				Author:			Shane Coates								 */
/*				Description:	Sprite Batch Factory						 */
/*																			 */
/*---------------------------------------------------------------------------*/

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <MathLib.h>

class Framework;
class Texture2D;
class SpriteBatch
{
public:

	enum ESpriteBatchType
	{
		NONE,
		IMMEDIATE,
		NON_IMMEDIATE,
	};


public:

	static SpriteBatch* Create(Framework *pFramework, ESpriteBatchType type);
	static void Destroy( SpriteBatch* pSpriteBatch);

	virtual void Begin() {}
	virtual void End() {}

	virtual void SetRenderColour(float r, float g, float b, float a);

	virtual void SetUVCoords(Vec4 UV);

	virtual void SetAlpha(float alpha) { m_alpha = alpha;}

	//TODO: convert xPos, yPos to Vec2
	virtual void DrawSprite(Texture2D* pTexture, const Vec2& position, bool centered) {}
	virtual void DrawSprite(Texture2D* pTexture, const Mat3x3& transform, bool centered) {}
	virtual void DrawSprite(Texture2D* pTexture, const Vec2& scale, const Mat3x3& transform, bool centered, Vec4 UV) {}
	virtual void DrawLine(const Vec2& pointA, const Vec2& pointB, const Vec4& colour) {}
	virtual void DrawPoint(const Vec2& point, const Vec4& colour) {}
	virtual void DrawQuad(const Mat3x3& transform, bool centered, const Vec4& colour) {}



protected:

	SpriteBatch(Framework *pFramework);

	virtual ~SpriteBatch() {}

	Framework* m_pFramework;

	//colour variables - used for tinting the rendered sprite
	float m_red, m_green, m_blue, m_alpha;
	float m_top, m_bottom, m_left, m_right;

private:

	


};

#endif