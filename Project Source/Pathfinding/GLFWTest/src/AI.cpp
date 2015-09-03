#include "AI.h"
#include "Framework.h"
#include "Pathfinding.h"
#include "AIStates.h"

AI::AI(Framework* framework, Texture2D* pTexture, std::list<Node*> _nodes, float _xSpace, float _ySpace) : PhysicsObject(framework, pTexture)
{
	m_pathfinding	= new Pathfinding(_nodes, _xSpace, _ySpace);
	//m_pathfinding->ResetDijkstraPoints(5);
	m_patrolState	= new Patrol(m_Framework, m_pathfinding, _nodes, this, _xSpace, _ySpace);
	m_targetState	= new Target(m_Framework, m_pathfinding, _nodes, this, _xSpace, _ySpace);
	m_seekState		= new Seek	(m_Framework, m_pathfinding, _nodes, this, _xSpace, _ySpace);
	m_EState = PATROL;

	m_drawPath = false;
}

AI::~AI()
{

}

void AI::Update(float dt)
{
	if(m_Framework->GetMouseDown())
	{
		Reset();
		m_targetState->UpdateTarget(m_Framework->GetMouseLocation(), 25);
		m_EState = TARGET;
	}

	if(m_Framework->GetKeyDown('F'))
	{
		Reset();
		m_EState = SEEK;
	}
			
	if(m_targetState->IsReached())
	{
		Reset();
		m_EState =	PATROL;
	}

	if(m_seekState->IsReached())
	{
		Reset();
		m_EState =	PATROL;
	}

	switch(m_EState)
	{
		case(PATROL):		m_patrolState->Update(dt);
			break;
		case(TARGET):		m_targetState->Update(dt);
			break;
		case(SEEK):			m_seekState->Update(dt);
			break;
	}
	PhysicsObject::Update(dt);
}

void AI::Draw()
{
	PhysicsObject::Draw();

	switch(m_EState)
	{
		case(PATROL):		m_patrolState->Draw();
			break;
		case(TARGET):		m_targetState->Draw();
			break;
		case(SEEK):			m_seekState->Draw();
			break;
	}

}

void AI::Reset()
{
	m_patrolState->Reset();
	m_targetState->Reset();
	m_seekState->Reset();
}