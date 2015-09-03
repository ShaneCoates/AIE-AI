#include "Framework.h"
#include <MathLib.h>
#include <Texture2D.h>
#include <FontRenderer.h>
#include "SpriteBatch.h"
#include "Game.h"
#include "SceneNode.h"
#include <iostream>

Framework::Framework(unsigned int &width, unsigned int &height, const char *title, bool fullscreen)
{
	glfwInit();

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	width = (fullscreen) ? mode->width : width;
	height = (fullscreen) ? mode->height : height;

	m_width = width;
	m_height = height;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(m_width, m_height, title, (fullscreen) ? glfwGetPrimaryMonitor() : NULL, NULL);

	ResetTimer();

	glfwMakeContextCurrent(window);	
	glewInit();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glOrtho(0.0, (GLdouble)width, 0.0, (GLdouble)height, 1.0, -1.0);

	m_spriteBatch = SpriteBatch::Create(this, SpriteBatch::NON_IMMEDIATE);
	m_fontRenderer = new GLFontRenderer();

	LoadDefaultFonts();

	m_world = new SceneNode(this);

	running = true;

}

Framework::~Framework()
{
	SpriteBatch::Destroy(m_spriteBatch);
	
	delete m_world;

	glfwTerminate();
}

bool Framework::FrameworkUpdate()
{
	if(!running)
		return true;

	glfwSwapBuffers(window);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	TickTimer();

	return glfwWindowShouldClose(window);
}

bool Framework::GetKeyDown(int key)
{
	return glfwGetKey(window, key);
}


bool Framework::GetMouseDown()
{
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) 
		return true;
	else
		return false;
}

Vec2 Framework::GetMouseLocation()
{
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	return Vec2(xPos, GetWindowHeight() - yPos);
}

void Framework::SetMouseLocation(Vec2 loc)
{
	glfwSetCursorPos(window, loc.x, loc.y);
}

void Framework::MoveMouse(Vec2 loc)
{
	glfwSetCursorPos(window, GetMouseLocation().x + loc.x, GetMouseLocation().y + loc.y);
}

void Framework::HideMouse(bool hidden)
{
	if(hidden)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Framework::Begin()
{
	m_spriteBatch->Begin();
}

void Framework::End()
{
	m_spriteBatch->End();
}

void Framework::SetColour(Vec4 colour)
{
	m_spriteBatch->SetRenderColour(colour.r, colour.g, colour.b, colour.a);
}

void Framework::SetAlpha(float alpha)
{
	m_spriteBatch->SetAlpha(alpha);
}

void Framework::DrawSprite(Texture2D *pTexture, Vec2& position, bool centered)
{
	m_spriteBatch->DrawSprite(pTexture, position, centered);
}

void Framework::DrawSprite(Texture2D *pTexture, Mat3x3 &transform, bool centered)
{
	m_spriteBatch->DrawSprite(pTexture, transform, centered);
}

void Framework::DrawSprite(Texture2D *pTexture, Vec2& scale, Mat3x3 &transform, bool centered, Vec4 UV)
{
	m_spriteBatch->DrawSprite(pTexture, scale, transform, centered, UV);
}

void Framework::DrawLine(const Vec2& pointA, const Vec2& pointB, const Vec4& colour)
{
	m_spriteBatch->DrawLine(pointA, pointB, colour);
}

void Framework::DrawPoint(const Vec2&point, const Vec4& colour)
{
	m_spriteBatch->DrawPoint(point, colour);
}

void Framework::DrawQuad(const Mat3x3& transform, bool centered, const Vec4& colour) 
{
	m_spriteBatch->DrawQuad(transform, centered, colour);
}

void Framework::DrawString(std::string fontName, std::string text, const Vec2& position)
{
	m_fontRenderer->DrawString(fontName, text, position);
}

void Framework::DrawString(std::string fontName, std::string text, const Vec2& position, const Vec4& colour)
{
	m_fontRenderer->DrawString(fontName, text, position, colour);
}

void Framework::LoadDefaultFonts()
{
	m_fontRenderer->LoadFont("KenPixel16",			"./fonts/kenpixel.ttf", 16.0f);
	m_fontRenderer->LoadFont("KenPixelBlocks16",	"./fonts/kenpixel_blocks.ttf", 16.0f);
	m_fontRenderer->LoadFont("KenPixelBlocks72",	"./fonts/kenpixel_blocks.ttf", 72.0f);
	m_fontRenderer->LoadFont("Arial16",				"./fonts/arial.ttf", 16.0f);

}

void Framework::ResetTimer()
{
	m_prevTime = glfwGetTime();
	m_totalTime = 0;
	m_deltaTime = 0;
}

double Framework::TickTimer()
{
	double currentTime = glfwGetTime();
	m_deltaTime = (float)(currentTime - m_prevTime);
	m_totalTime += m_deltaTime;
	m_prevTime = currentTime;
	return m_deltaTime;
}

double Framework::GetDeltaTime()
{
	return m_deltaTime;
}

void Framework::AddWorldChild(SceneNode *child)
{
	m_world->AddChild(child);
}

void Framework::DrawWorld()
{
	m_world->Draw();
}

void Framework::TranslateWorld(const Vec2 &translate)
{
	m_world->GetLocalTransform()->Translate(translate);
}

void Framework::ScaleWorld(const Vec2 &scale)
{
	m_world->GetLocalTransform()->SetScale(Vec2(m_world->GetLocalTransform()->GetScale().x + scale.x, m_world->GetLocalTransform()->GetScale().y + scale.y));
}

Vec4 Framework::GetPlayerUV(const char* fileName, Texture2D* tex)
{	
	tinyxml2::XMLDocument doc;
	Vec4 UVCoords = Vec4(0, 0, 0, 0);;
	if(doc.LoadFile("./images/player/playerSpritesheet.xml") == tinyxml2::XML_NO_ERROR)
	{
		const char * width = doc.FirstChildElement("TextureAtlas")->FirstChildElement("SubTexture")->Attribute("width");

		auto element = doc.FirstChildElement("TextureAtlas")->FirstChildElement();
		while(element != NULL)
		{
			if(strcmp(fileName, element->Attribute("name")) == 0)
			{
					UVCoords = Vec4(tex->GetHeight() - (atoi(element->Attribute("y")) + atoi(element->Attribute("height"))),
											tex->GetHeight() - atoi(element->Attribute("y")), 
											atoi(element->Attribute("x")),
											atoi(element->Attribute("x")) + atoi(element->Attribute("width"))			
											);
					break;
			}
			element = element->NextSiblingElement();
		}
	}
	return UVCoords;
}

Vec4 Framework::GetTileUV(const char* fileName, Texture2D* tex)
{	
	Vec4 UVCoords = Vec4(0, 0, 0, 0);
	tinyxml2::XMLDocument doc;

	if(doc.LoadFile("./images/spritesheets/sheet.xml") == tinyxml2::XML_NO_ERROR)
	{
		const char * width = doc.FirstChildElement("TextureAtlas")->FirstChildElement("SubTexture")->Attribute("width");


		auto element = doc.FirstChildElement("TextureAtlas")->FirstChildElement();
		while(element != NULL)
		{
			if(strcmp(fileName, element->Attribute("name")) == 0)
			{
					UVCoords = Vec4(tex->GetHeight() - atoi(element->Attribute("y")), 
											tex->GetHeight() - (atoi(element->Attribute("y")) + atoi(element->Attribute("height"))),
											atoi(element->Attribute("x")),
											atoi(element->Attribute("x")) + atoi(element->Attribute("width"))			
											);
					break;
			}
			element = element->NextSiblingElement();
		}
	}

	return UVCoords;	
}

float Framework::Curve(Curve::CURVE_TYPE type, float t, float start, float end)
{
	return Curve::CurveFunc(type, t, start, end);
}