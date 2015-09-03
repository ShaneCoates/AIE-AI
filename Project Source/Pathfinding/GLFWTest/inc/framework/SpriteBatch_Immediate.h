/*---------------------------------------------------------------------------*/
/*																			 */	
/*				Author:			Shane Coates								 */
/*				Description:	Sprite Batch Factory						 */
/*																			 */
/*---------------------------------------------------------------------------*/

#ifndef SPRITEBATCH_IMMEDIATE_H
#define SPRITEBATCH_IMMEDIATE_H

#include "SpriteBatch.h"

class Texture2D;
class Framework;
class SpriteBatch_Immediate : public SpriteBatch
{
public:

	SpriteBatch_Immediate(Framework *pFramework);

	virtual void Begin();
	virtual void End();

	virtual void DrawSprite(Texture2D* pTexture, const Vec2& position, bool centered);
	virtual void DrawSprite(Texture2D* pTexture, const Mat3x3& transform, bool centered);
	virtual void DrawSprite(Texture2D* pTexture, const Vec2& scale, const Mat3x3& transform, bool centered, Vec4 UV);

protected:

	

private:

};




#endif