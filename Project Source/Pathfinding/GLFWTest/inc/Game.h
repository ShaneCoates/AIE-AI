/*-----------------------------------------------------------------------------
 Author: Shane Coates
 Description:
 This is the game class, it will encapsulate window management and the main
 game loop...
-----------------------------------------------------------------------------*/
#pragma once
#ifndef GAME_H
#define GAME_H

#include <MathLib.h>

class GameStateManager;
class Framework;
class Texture2D;
class SceneNode;
class SpriteSceneNode;
class SplashState;
class GameState;
class MenuState;
class TestState;


class Game
{
public:

	// constructor
	Game(unsigned int windowWidth, unsigned int windowHeight, const char *windowTitle, bool fullscreen);

	// destructor
	~Game();

	// returns when the main game loop has finished
	void RunGame();

	Framework* GetFramework()  {return framework;};

	unsigned int GetWindowWidth() {return m_windowWidth;}
	unsigned int GetWindowHeight() {return m_windowHeight;}


private:

	// called each frame from within RunGame()
	void Update();

	// called each frame from within RunGame()
	void Draw();

	void CheckUserInput();

	GameStateManager *GetGameStateManager() { return m_gameStateManager;}

private:

	unsigned int m_windowWidth;
	unsigned int m_windowHeight;


	Vec2 m_center;

	bool m_gameOver;

	Texture2D*				m_backgroundTexture;

	Texture2D*				m_cursorTexture;
	SpriteSceneNode*		m_cursor;

	GameStateManager*		m_gameStateManager;

	Framework*				framework;

	SpriteSceneNode*		m_background;

	GameState*				m_gameState;
	TestState*				m_testState;


	//TODO: place game related variables here
	//TODO: place game related functions here

};

#endif


