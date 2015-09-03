#include "GameStateManager.h"

// IGameState
//-----------------------------------------------------------------------------
IGameState::IGameState(GameStateManager* pGameStateManager)
{
	m_gameStateManager = pGameStateManager;
}

IGameState::~IGameState()
{
	//intentionally left blank
}

void IGameState::Update(float dt)
{
	//intentionally left blank
}

void IGameState::Draw()
{
	//intentionally left blank
}
//-----------------------------------------------------------------------------
// IGameState


//constructor
GameStateManager::GameStateManager(Framework* framework)
{
	m_framework = framework;
}

//destructor
GameStateManager::~GameStateManager()
{

}

//should be called each frame by the "Game" class
void GameStateManager::UpdateGameStates(float dt)
{
	ProcessCommands();

	bool blocking = false;

	for(auto itr = m_gameStateStack.begin(); itr != m_gameStateStack.end(); itr++)
	{

		if(*itr == nullptr)
			continue;
		for(auto itr2 = itr+1; itr2 != m_gameStateStack.end(); itr2++)
		{
			if((*itr2)->GetUpdateBlocking())
			{
				blocking = true;
				break;
			}
		}

		if(blocking == false || *itr == m_gameStateStack.back())
			(*itr)->Update(dt);
	}
}

void GameStateManager::DrawGameStates()
{
	bool blocking = false;

	for(auto itr = m_gameStateStack.begin(); itr != m_gameStateStack.end(); itr++)
	{
		if(*itr == nullptr)
			continue;
		for(auto itr2 = itr+1; itr2 != m_gameStateStack.end(); itr2++)
		{
			if((*itr2)->GetDrawBlocking())
			{
				blocking = true;
				break;
			}
		}

		if(blocking == false || *itr == m_gameStateStack.back())
			(*itr)->Draw();
	}
}

void GameStateManager::ProcessCommands()
{
	for(unsigned int i = 0; i < m_commands.size(); i++)
	{
		if(m_commands[i].cmd == E_PUSH)
		{
			auto iter = m_availableStates.find(m_commands[i].name);
			if(iter != m_availableStates.end())
			{
				m_gameStateStack.push_back(iter->second);
			}
		}
		else if(m_commands[i].cmd == E_POP)
		{
			if(m_gameStateStack.size() > 0)
				m_gameStateStack.pop_back();
		}
	}

	//now that all commans have been processed, clear the list for the next frame...
	m_commands.clear();
}


//used to manipulate the game state stack
void GameStateManager::SetState(const char* name,  IGameState* pState, Framework* framework)
{
	m_framework = framework;

	auto iter = m_availableStates.find(name);
	if(iter != m_availableStates.end())
	{
		delete iter->second;
	}

	m_availableStates[ name ] = pState;
}

void GameStateManager::PushState(const char *name, bool updateBlocking, bool drawBlocking)
{
	m_availableStates[name]->SetUpdateBlocking(updateBlocking);
	m_availableStates[name]->SetDrawBlocking(drawBlocking);

	SCommand command;
	command.name = name;
	command.cmd = E_PUSH;
	m_commands.push_back(command);
}

void GameStateManager::PopState()
{
	SCommand command;
	command.cmd = E_POP;

	m_commands.push_back(command);
}