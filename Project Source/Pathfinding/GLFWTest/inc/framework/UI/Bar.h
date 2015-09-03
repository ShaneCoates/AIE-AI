/*-----------------------------------------------------------------------------
		Author:			Shane Coates
		Description:	Bar class for sliders
						
-----------------------------------------------------------------------------*/

#ifndef BAR_H
#define	BAR_H

#include "SceneNode.h"
#include "SpriteSceneNode.h"

class Texture2D;
class Framework;
class Vec2;
class Framework;

class Bar : public SceneNode
{
public:

	Bar(Framework* framework, Vec2 size, bool base = false);
	virtual ~Bar();

	virtual void Update(float dt);

	virtual void Draw();

	unsigned int GetPercentage();

	unsigned int GetPoint();

	void SetPoint(unsigned int point);

	void SetPercentage(float per);

	void SetOrange();	
		
	void SetBlue();

	void SetYellow();
	
	void SetGreen();

protected:
private:

	unsigned int m_height;
	float m_percentage;

	Vec2 m_position;
	Vec2 m_size;
	
	float m_width;
	float m_sideWidth;
	float m_leftX;
	float m_rightX;

	Framework* m_framework;

	Texture2D* m_spriteCenter;
	Texture2D* m_spriteLeft;
	Texture2D* m_spriteRight;

	SpriteSceneNode* m_left;
	SpriteSceneNode* m_center;
	SpriteSceneNode* m_right;
};
#endif