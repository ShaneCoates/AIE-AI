/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	GAME FRAMEWORK
						Contains:
						 - GLFW, GLEW and SOIL
						 - Window opening, closing, resizing
						 - User keyboard and mouse input
						 - Loading and drawing textures to the screen

-----------------------------------------------------------------------------*/

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <MathLib.h>
#include <tinyxml2.h>
#include "Texture2D.h"
#include <stdlib.h>
#include <time.h>
#include "Curve.h"

#include <string>

class SpriteBatch;

class Asset;
class Texture2D;
class GLFontRenderer;
class SceneNode;

class Framework
{
public:

	Framework(unsigned int &width, unsigned int &height, const char *title, bool fullscreen);
	~Framework();
	bool FrameworkUpdate();
	void CreateSprite(const char* address);
	bool GetKeyDown(int key);
	bool GetMouseDown();
	Vec2 GetMouseLocation();
	void SetMouseLocation(Vec2 loc);
	void MoveMouse(Vec2 loc);
	void HideMouse(bool hidden);

	void Begin();
	void End();

	void DrawSprite(Texture2D *pTexture, Vec2& position, bool centered);
	void DrawSprite(Texture2D *pTexture, Mat3x3 &transform, bool centered);
	void DrawSprite(Texture2D *pTexture, Vec2& scale, Mat3x3 &transform, bool centered, Vec4 UV);
	void DrawLine(const Vec2& pointA, const Vec2& pointB, const Vec4& colour);
	void DrawPoint(const Vec2&point, const Vec4& colour);
	void DrawQuad(const Mat3x3& transform, bool centered, const Vec4& colour);

	void DrawString(std::string fontName, std::string text, const Vec2& position);
	void DrawString(std::string fontName, std::string text, const Vec2& position, const Vec4& colour);

	unsigned int GetWindowWidth()		{return m_width;}
	unsigned int GetWindowHeight()		{return m_height;}

	float GetSquareUnit()				{return (float)m_height / 100;}

	void Quit()							{running = false;}

	void SetColour(Vec4 colour);
	void SetAlpha(float alpha);
		
	void ResetTimer();
	double TickTimer();
	double GetDeltaTime();

	inline GLFontRenderer *GetFontRenderer() { return m_fontRenderer; }

	void AddWorldChild(SceneNode *child);

	void DrawWorld();

	void TranslateWorld(const Vec2 &translate);
	void ScaleWorld(const Vec2 &scale);

	Vec4 GetPlayerUV(const char* fileName, Texture2D* tex); 
	Vec4 GetTileUV(const char* fileName, Texture2D* tex); 

	SpriteBatch * GetSpriteBatch() { return m_spriteBatch; }

	//curves:
	float Curve(Curve::CURVE_TYPE type, float t, float start, float end);

protected:

	void LoadDefaultFonts();

	GLFWwindow* window;
	Asset*		background;

private:

	SpriteBatch* m_spriteBatch;
	GLFontRenderer * m_fontRenderer;

	int		m_width;
	int		m_height;

	double	m_frameLength;
	double	m_prevTime;
	double	m_totalTime;
	double	m_deltaTime;

	bool running;

	SceneNode* m_world;
};
#endif // !FRAMEWORK_H
