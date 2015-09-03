/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Sprite Scene Node

-----------------------------------------------------------------------------*/

#ifndef SPRITESCENENODE_H
#define	SPRITESCENENODE_H

#include "SceneNode.h"

class Framework;
class Texture2D;
class Vec4;

class SpriteSceneNode : public SceneNode
{
public:
	SpriteSceneNode(Framework *framework, Texture2D *texture);
	virtual ~SpriteSceneNode();

	virtual void Draw();

	void SetTextureScaleTransformInPixels(const Vec2& scale);

	Vec4 GetUVCoords()		{return m_UVCoords;}

	void SetUVCoords(const Vec4& UV);

	void SetUVCoordsInPixels(const Vec4& UV);

	void SetSize(const Vec2& scale);
		
	Vec2 GetSize();

	void SetColour(Vec4 colour)			{m_colour = colour;}

	inline void SetTexture(Texture2D *texture) {m_Texture = texture;}
	inline Texture2D *GetTexture() { return m_Texture;}

	void SetCentered(bool centered)		{m_centered = centered;}
	bool GetCentered()					{return m_centered;}

	unsigned int GetWidth();

	unsigned int GetHeight();

	bool GetMouseOver();


protected:

	Vec2 m_size;
	Vec4 m_UVCoords;
	Vec4 m_colour;
	Texture2D *m_Texture;
	bool m_centered;
};


#endif