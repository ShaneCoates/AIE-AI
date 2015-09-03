/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Label class
						made up using a box


-----------------------------------------------------------------------------*/

#ifndef LABEL_H
#define	LABEL_H

#include "SpriteSceneNode.h"

class Framework;
class Texture2D;
class Vec2;
class Box;

class Label : public SpriteSceneNode
{
	
public:

	Label(Framework* framework, Texture2D* pTexture, Vec2 boxSize);

	virtual ~Label();

	virtual void Update(float dt);

	virtual void Draw();

	void SetText(const char* text);

protected:
private:

	const char* m_text;

	Vec2 m_buttonSize;
	Vec2 m_minBounds;
	Vec2 m_maxBounds;
	
	Vec2 m_textPos;
	
	Box* m_box;

	Texture2D* m_texture;
};
#endif