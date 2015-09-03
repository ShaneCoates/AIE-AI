/*-----------------------------------------------------------------------------
		Author:			Shane Coates
		Description:	Basic Game State manager
						Handles a stack of game states
-----------------------------------------------------------------------------*/

#ifndef GAMESTATEMANAGER_H
#define	GAMESTATEMANAGER_H

#include <map>
#include <vector>

//predefinition
class GameStateManager;
class Framework;
class IGameState
{
public:

	IGameState(GameStateManager* pGameStateManager);
	virtual ~IGameState();

	virtual void Update(float dt);
	virtual void Draw();

	void SetUpdateBlocking	(bool updateBlocking)	{m_updateBlocking = updateBlocking;}
	void SetDrawBlocking	(bool drawBlocking)		{m_drawBlocking = drawBlocking;}

	bool GetUpdateBlocking()						{return m_updateBlocking;}
	bool GetDrawBlocking()							{return m_drawBlocking;}

protected:

	GameStateManager * m_gameStateManager;


private:

	bool m_updateBlocking;
	bool m_drawBlocking;
};


class GameStateManager
{
public:

	//constructor
	GameStateManager(Framework* framework);

	//destructor
	virtual ~GameStateManager();

	//should be called each frame by the "Game" class
	void UpdateGameStates(float dt);
	void DrawGameStates();

	//used to manipulate the game state stack
	void SetState(const char* name,  IGameState* pState, Framework* framework);

	//void PushState(const char *name);
	//void PushState(const char *name, bool updateBlocking);
	void PushState(const char *name, bool updateBlocking = false, bool drawBlocking = false);

	void PopState();

protected:

	void ProcessCommands();

protected:



	//contains all of the available game states that have been
	//registered with the game state manager
	std::map<const char *, IGameState *> m_availableStates;

	//list of game states that are being updated and drawn
	std::vector< IGameState* > m_gameStateStack;

	
	enum ECommands
	{
		E_PUSH,
		E_POP,
	};


	struct SCommand
	{
		const char *name;
		ECommands cmd;
	};

	std::vector< SCommand > m_commands;
private:

	Framework* m_framework;

};

#endif