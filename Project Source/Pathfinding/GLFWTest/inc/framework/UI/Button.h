/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Button class
						made up using a box
						box texture will change on press
						will return a true value if pressed

-----------------------------------------------------------------------------*/

#ifndef BUTTON_H
#define	BUTTON_H

#include "SpriteSceneNode.h"

class Framework;
class Texture2D;
class Vec2;
class Box;

class Button : public SpriteSceneNode
{
	
public:

	Button(Framework* framework, Texture2D* pTexture, Texture2D* pPressedTexture, Vec2 boxSize);

	virtual ~Button();

	virtual void Update(float dt);

	virtual void Draw();

	bool GetPressed();

	void SetSelected(bool sel);
	bool GetSelected();

	void SetEnabled(bool en)				{enabled = en;}
	bool GetEnabled()						{return enabled;}

	const char* GetText()					{return m_text;}

	void SetText(const char* text);

	void SetControllerButtonDown(bool btn);

protected:
private:

	bool pressed;
	bool selected;
	bool mouseOver;
	bool btnDown;

	bool enabled;

	void CheckMousePos();

	const char* m_text;

	Vec2 m_buttonSize;
	Vec2 m_minBounds;
	Vec2 m_maxBounds;
	
	Vec2 m_textPos;

	Vec2 m_mouseLocation;
	
	Box* m_box;

	Texture2D* m_texture;
	Texture2D* m_pressedTexture;

	Framework* m_framework;
};
#endif