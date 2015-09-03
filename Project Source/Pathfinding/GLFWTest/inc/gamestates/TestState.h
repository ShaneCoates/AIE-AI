/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Basic Test State
						Used to test new componants and implementations
						Will be removed before final release

-----------------------------------------------------------------------------*/

#ifndef TESTSTATE_H
#define	TESTSTATE_H

#include "GameStateManager.h"
#include <list>

class GameStateManager;
class Framework;
class Vec2;
class Node;
class Texture2D;
class AI;
class SpriteSceneNode;

#define X_SPACING 25
#define Y_SPACING 25
#define NUM_AI 10


class TestState : public IGameState
{
public:

	TestState(GameStateManager* pGameStateManager, Framework* framework);

	virtual ~TestState();

	virtual void Update(float dt);

	virtual void Draw();

	void GetUserInput(float dt);

protected:
private:

	Framework* m_framework;

	std::list<Node*> m_nodes;

	Texture2D* m_shipTexture;
	AI* m_ship[NUM_AI];

	Texture2D* m_meteorTexture;
	std::list<SpriteSceneNode*> m_meteors;

	Texture2D* m_backgroundTexture;
	SpriteSceneNode* m_background;

	bool m_keyDownLast;
	bool m_nodeDrawing;
	bool m_pathDrawing;
	unsigned int m_pathDrawingIndex;

	void Reset();
	void CalculateNeighbours();
	
};

#endif