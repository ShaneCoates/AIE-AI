/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Base Box class
						To be used for buttons, textboxes
						and displaying all sorts of information

						box will take a single sprite or image from a sprite sheet
						and nine-patch it for easy resizing


-----------------------------------------------------------------------------*/

#ifndef BOX_H
#define	BOX_H

#include "SpriteSceneNode.h"

class Framework;
class Texture2D;
class Vec2;
class Mat3x3;

class Box : public SpriteSceneNode
{
	
public:

	Box(Framework* framework, Texture2D* pTexture, Vec2 UVSize, Vec2 boxSize);

	virtual ~Box();

	virtual void Update(float dt);

	virtual void Draw();

	void SetUVSize();

	void SetBoxSize(Vec2 size);

	void SetBoxTexture(Texture2D* tex);


protected:
private:

	Vec2 m_UVSize;
	Vec2 m_boxSize;
	float m_xPos[4];
	float m_yPos[4];

	float m_sideY;
	float m_topX;

	void SetSize();

	void SetUVs();

	void SetPositions();

	SpriteSceneNode* TopLeft;
	SpriteSceneNode* Top;
	SpriteSceneNode* TopRight;

	SpriteSceneNode* Left;
	SpriteSceneNode* Center;
	SpriteSceneNode* Right;

	SpriteSceneNode* BottomLeft;
	SpriteSceneNode* Bottom;
	SpriteSceneNode* BottomRight;

	Framework* m_framework;
};
#endif