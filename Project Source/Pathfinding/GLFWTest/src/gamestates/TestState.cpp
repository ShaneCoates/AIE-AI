#include "gamestates/TestState.h"
#include "Framework.h"
#include "Node.h"
#include "Utils.h"
#include "Framework/PathFinding.h"
#include "AI.h"
#include "AIStates.h"

TestState::TestState(GameStateManager* pGameStateManager, Framework* framework) : IGameState(pGameStateManager)
{	
	m_framework = framework;

	m_nodeDrawing = false;
	m_keyDownLast = false;
	m_pathDrawing = false;

	m_meteorTexture = new Texture2D("images/meteor.png", false);

	for(int i = 0; i < 10; i++)
	{
		SpriteSceneNode *_meteor = new SpriteSceneNode(m_framework, m_meteorTexture);
		_meteor->SetCentered(true);
		_meteor->GetLocalTransform()->SetTranslation(Vec2(Utils::RandomNumber(0, m_framework->GetWindowWidth()), Utils::RandomNumber(0, m_framework->GetWindowHeight())));
		_meteor->SetSize(Vec2(2*X_SPACING, 2*Y_SPACING));
		m_meteors.push_back(_meteor);
	}

	for(int x = 0; x < m_framework->GetWindowWidth(); x+= X_SPACING)
	{
		for(int y = 0; y < m_framework->GetWindowHeight(); y+= Y_SPACING)
		{
			bool overlap = false;
			for(auto itr = m_meteors.begin(); itr != m_meteors.end(); itr++)
			{
				Vec2 meteorTrans = (*itr)->GetGlobalTransform().GetTranslation();

				if(	meteorTrans.x - (2 * X_SPACING) < x &&
					meteorTrans.x + (2 * X_SPACING) > x &&
					meteorTrans.y - (2 * Y_SPACING) < y &&
					meteorTrans.y + (2 * Y_SPACING) > y)
					overlap = true;
			}
			if(!overlap)
			{
				Node* _node = new Node(m_framework, Vec2( x, y));
				for(auto itr = m_meteors.begin(); itr != m_meteors.end(); itr++)
				{
					Vec2 meteorTrans = (*itr)->GetGlobalTransform().GetTranslation();

					if(	meteorTrans.x - (3 * X_SPACING) < x &&
						meteorTrans.x + (3 * X_SPACING) > x &&
						meteorTrans.y - (3 * Y_SPACING) < y &&
						meteorTrans.y + (3 * Y_SPACING) > y)
					_node->SetTarget(true);
				}


				m_nodes.push_back(_node);	

			}
		}
	}
	

	CalculateNeighbours();
	Reset();
	m_shipTexture = new Texture2D("images/player.png", false);

	for(int i = 0; i < NUM_AI; i++)
	{
		m_ship[i] = new AI(m_framework, m_shipTexture, m_nodes, X_SPACING, Y_SPACING);
		m_ship[i]->GetLocalTransform()->SetTranslation(Vec2(m_framework->GetWindowWidth() * 0.5f, m_framework->GetWindowHeight() * 0.5f));
		m_ship[i]->SetSize(Vec2(X_SPACING, Y_SPACING));
		m_ship[i]->SetCentered(true);
	}

	m_pathDrawingIndex = 0;
	m_backgroundTexture = new Texture2D("images/background.png", true);
	m_background = new SpriteSceneNode(m_framework, m_backgroundTexture);
	m_background->SetUVCoordsInPixels(Vec4(0,  m_framework->GetWindowHeight(), 0, m_framework->GetWindowWidth()));
	m_background->SetSize(Vec2(m_framework->GetWindowWidth(), m_framework->GetWindowHeight()));
}

TestState::~TestState()
{
	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
		delete (*itr);
	delete m_background;
	delete m_backgroundTexture;
}

void TestState::Update(float dt)
{

	GetUserInput(dt);

	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)	
		(*itr)->Update(dt);


	for(auto itr = m_meteors.begin(); itr != m_meteors.end(); itr++)
		(*itr)->Update(dt);
	

	for(int i = 0; i < NUM_AI; i++)
	{
		m_ship[i]->Update(dt);
	}


}

void TestState::Draw()
{	
	m_background->Draw();
	//DrawNeighbours();	
	for(auto itr = m_meteors.begin(); itr != m_meteors.end(); itr++)
		(*itr)->Draw();
	//DrawPath();
	for(int i = 0; i < NUM_AI; i++)
		m_ship[i]->Draw();	
	if(m_nodeDrawing)
	{
		for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
			(*itr)->Draw();
	}
	if(m_pathDrawing)
		m_ship[m_pathDrawingIndex]->SetDrawPath(true);
	else
		m_ship[m_pathDrawingIndex]->SetDrawPath(false);

}

void TestState::GetUserInput(float dt)
{
	if(m_framework->GetKeyDown(GLFW_KEY_1))
	{
		if(!m_keyDownLast)
		{
			if(m_nodeDrawing)
				m_nodeDrawing = false;
			else
				m_nodeDrawing = true;
		}
		m_keyDownLast = true;
	}
	else if(m_framework->GetKeyDown(GLFW_KEY_2))
	{
		if(!m_keyDownLast)
		{
			if(m_pathDrawing)
				m_pathDrawing = false;
			else
				m_pathDrawing = true;
		}
		m_keyDownLast = true;
	}
	else if(m_framework->GetKeyDown(GLFW_KEY_TAB))
	{
		if(m_pathDrawingIndex < NUM_AI - 1)
			m_pathDrawingIndex++;
		else
			m_pathDrawingIndex = 0;

		for(int i = 0; i < NUM_AI; i++)
			m_ship[i]->SetDrawPath(false);
	}
	else
		m_keyDownLast = false;

	if(m_framework->GetKeyDown('R'))
	{
		Reset();
	}
}
	
void TestState::CalculateNeighbours()
{
	for(auto node1 = m_nodes.begin(); node1 != m_nodes.end(); node1++)
	{
		(*node1)->ClearNeighbours();
		(*node1)->SetCost(1);
		for(auto node2 = m_nodes.begin(); node2 != m_nodes.end(); node2++)
		{
			float x = abs((*node1)->GetGlobalTransform().GetTranslation().x - (*node2)->GetGlobalTransform().GetTranslation().x);
			float y = abs((*node1)->GetGlobalTransform().GetTranslation().y - (*node2)->GetGlobalTransform().GetTranslation().y);
			
			Vec2 dist = Vec2(x, y);	
			if(dist.Length() < sqrt((X_SPACING * X_SPACING) + (Y_SPACING * Y_SPACING)))
			{
				(*node1)->AddNeighbours(*node2);
			}
		}
	}
}


void TestState::Reset()
{
	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
	{
		(*itr)->SetOpen(false);
		(*itr)->SetParent(nullptr);
		(*itr)->m_GScore = 1;
	}

}