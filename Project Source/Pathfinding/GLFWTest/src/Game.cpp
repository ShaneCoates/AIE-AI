#include "Game.h"
#include "GameStateManager.h"
#include <MathLib.h>
#include "Framework.h"
#include <iostream>
#include "Texture2D.h"
#include "gamestates\TestState.h"
#include "SpriteSceneNode.h"

// constructor
Game::Game(unsigned int windowWidth, unsigned int windowHeight, const char *windowTitle, bool fullscreen)
{
	framework = new Framework(windowWidth, windowHeight, windowTitle, fullscreen);
	
	m_windowWidth	= windowWidth;
	m_windowHeight	= windowHeight;

	m_gameOver		= false;
	
	m_gameStateManager = new GameStateManager(framework);

	m_testState			= new TestState			(m_gameStateManager, framework);

	m_gameStateManager->SetState("TestState", m_testState, framework);


	m_gameStateManager->PushState("TestState", true, true);

}

// destructor
Game::~Game()
{
	delete m_testState;

	delete framework;
}

// returns when the main game loop has finished
void Game::RunGame()
{
	while (!framework->FrameworkUpdate())
	{
		framework->HideMouse(false);
		Update();
		Draw();
	} 
}

// called each frame from within RunGame()
void Game::Update()
{

	m_gameStateManager->UpdateGameStates((float)framework->GetDeltaTime());

}

// called each frame from within RunGame()
void Game::Draw()
{
	framework->Begin();

	framework->DrawWorld();

	m_gameStateManager->DrawGameStates();

	framework->End();
}