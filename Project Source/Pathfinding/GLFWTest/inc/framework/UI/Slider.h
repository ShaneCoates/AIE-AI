///*-----------------------------------------------------------------------------
//
//		Author:			Shane Coates
//		Description:	Basic Slider class
//						used to display a percentage value
//
//-----------------------------------------------------------------------------*/
//
//#ifndef SLIDER_H
//#define	SLIDER_H
//
//
//#include "SpriteSceneNode.h"
//
//{
//class Framework;
//class Texture2D;
//class Vec2;
//class Mat3x3;
//class Bar;
//
//class Slider : public SceneNode
//{
//	
//public:
//
//	Slider(Framework* framework, Vec2 size);
//
//	virtual ~Slider();	
//
//	virtual void Update(float dt);
//
//	unsigned int GetPercentage();
//
//	void SetPercentage(float per);
//
//	void SetOrange();	
//		
//	void SetBlue();
//
//	void SetYellow();
//	
//	void SetGreen();
//
//	void SetModifiable(bool modify);
//
//	void CheckInput();
//
//
//protected:
//
//
//private:
//
//	Bar* m_baseBar;
//	Bar* m_bar;
//
//	bool m_modifiable;
//
//	Vec2 m_barSize;
//	Vec2 m_minBounds;
//	Vec2 m_maxBounds;
//	Vec2 m_mouseLocation;
//
//
//	Texture2D* m_pointerTexture;
//	SpriteSceneNode* m_pointer;
//
//};
//}
//#endif
//
