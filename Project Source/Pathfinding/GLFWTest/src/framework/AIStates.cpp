#include "AIStates.h"
#include "framework.h"
#include <math.h>
#include <iostream>
#include "PathFinding.h"
#include "Utils.h"

Patrol::Patrol(Framework* _framework, Pathfinding* _pathfinding, std::list<Node*> _nodes, AI* _AI, float _xSpace, float _ySpace)
{
	m_AI = _AI;
	m_pathfinding = _pathfinding;
	m_nodes = _nodes;
	m_framework = _framework;
}

void Patrol::Update(float dt)
{
	float x = m_AI->GetSize().x;
	float y = m_AI->GetSize().y;
	
	if(m_path.size() <= 2)
	{
		bool startFound = false;

		Vec2 shipTrans = m_AI->GetGlobalTransform().GetTranslation();
		while(!startFound)
		{
			for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
			{
				(*itr)->SetStart(false);
				(*itr)->SetFinish(false);
				(*itr)->SetOpen(false);
				(*itr)->SetParent(nullptr);
				(*itr)->m_GScore = 1;
				Vec2 nodeTrans = (*itr)->GetGlobalTransform().GetTranslation();

				if(	shipTrans.x - x < nodeTrans.x &&
					shipTrans.x + x > nodeTrans.x &&
					shipTrans.y - y < nodeTrans.y &&
					shipTrans.y + y > nodeTrans.y)
				{
					(*itr)->SetStart(true);
					startFound = true;
				}
			}
			if(!startFound)
			{
				x *= 2;
				y *= 2;
			}
		}
		auto finishNode = m_nodes.begin();
		unsigned int rand = Utils::RandomNumber(0, m_nodes.size() - 1);
		for(int i = 0; i < rand; i++)
			finishNode++;

		(*finishNode)->SetFinish(true);

		m_pathfinding->UpdateNodeList(m_nodes);

		m_path.clear();
		m_pathfinding->GetAStarPath(m_path);
	}

	if(m_path.size() > 1)
	{
		m_AI->TurnTowards(m_path.front()->GetGlobalTransform().GetTranslation(), 10.0f);

		Vec2 shipTrans = m_AI->GetGlobalTransform().GetTranslation();
		Vec2 nodeTrans = m_path.front()->GetGlobalTransform().GetTranslation();

			if(	shipTrans.x - x < nodeTrans.x &&
				shipTrans.x + x > nodeTrans.x &&
				shipTrans.y - y < nodeTrans.y &&
				shipTrans.y + y > nodeTrans.y)
			m_path.pop_front();
	}
}

void Patrol::Draw()
{
	if(m_AI->GetDrawPath())
	{
		if(m_path.size() > 0)
		{	
			for(auto node1 = m_path.begin(); node1 != m_path.end(); node1++)
			{
				m_framework->DrawLine(	m_AI->GetGlobalTransform().GetTranslation(), 
											m_path.front()->GetGlobalTransform().GetTranslation(), 
											Vec4(1, 0, 0, 1));
				(*node1)->SetColour(Vec4(0, 0, 1, 1));
					
				auto node2 = node1;
				node2++;
				if(node2 != m_path.end())
				{
					m_framework->DrawLine(	(*node1)->GetGlobalTransform().GetTranslation(), 
											(*node2)->GetGlobalTransform().GetTranslation(), 
											Vec4(1, 0, 0, 1));
				}
			}
		}
	}
}

void Patrol::Reset()
{
	m_path.clear();
}

Target::Target(Framework* _framework, Pathfinding* _pathfinding, std::list<Node*> _nodes, AI* _AI, float _xSpace, float _ySpace)
{
	m_AI = _AI;
	m_pathfinding = _pathfinding;
	m_framework = _framework;
	m_nodes = _nodes;
	m_reached = false;

	m_width = m_AI->GetSize().x;
	m_height = m_AI->GetSize().y;

}

void Target::Update(float dt)
{
	m_width = m_AI->GetSize().x;
	m_height = m_AI->GetSize().y;
	
	if(m_path.size() > 1)
	{
		m_AI->TurnTowards(m_path.front()->GetGlobalTransform().GetTranslation(), 10.0f);

		Vec2 shipTrans = m_AI->GetGlobalTransform().GetTranslation();
		Vec2 nodeTrans = m_path.front()->GetGlobalTransform().GetTranslation();

			if(	shipTrans.x - m_width < nodeTrans.x &&
				shipTrans.x + m_width > nodeTrans.x &&
				shipTrans.y - m_height < nodeTrans.y &&
				shipTrans.y + m_height > nodeTrans.y)
			m_path.pop_front();
	}
	else
		m_reached = true;
}

void Target::Draw()
{
	if(m_AI->GetDrawPath())
	{
		if(m_path.size() > 0)
		{	
			m_framework->DrawLine(	m_AI->GetGlobalTransform().GetTranslation(), 
											m_path.front()->GetGlobalTransform().GetTranslation(), 
											Vec4(1, 0, 0, 1));
			for(auto node1 = m_path.begin(); node1 != m_path.end(); node1++)
			{
				(*node1)->SetColour(Vec4(0, 0, 1, 1));
					
				auto node2 = node1;
				node2++;
				if(node2 != m_path.end())
				{
					m_framework->DrawLine(	(*node1)->GetGlobalTransform().GetTranslation(), 
											(*node2)->GetGlobalTransform().GetTranslation(), 
											Vec4(1, 0, 0, 1));
				}
			}
		}
	}
}

void Target::Reset()
{
	m_reached = false;
	m_path.clear();

}

void Target::UpdateTarget(Vec2 _pos, float _range)
{
	m_width = m_AI->GetSize().x;
	m_height = m_AI->GetSize().y;

	m_pathfinding->SetFinish(_pos, _range);
	bool startFound = false;

	Vec2 shipTrans = m_AI->GetGlobalTransform().GetTranslation();
	while(!startFound)
	{
		for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
		{
			(*itr)->SetStart(false);
			(*itr)->SetOpen(false);
			(*itr)->SetParent(nullptr);
			(*itr)->m_GScore = 1;
			Vec2 nodeTrans = (*itr)->GetGlobalTransform().GetTranslation();

			if(	shipTrans.x - m_width < nodeTrans.x &&
				shipTrans.x + m_width > nodeTrans.x &&
				shipTrans.y - m_height < nodeTrans.y &&
				shipTrans.y + m_height > nodeTrans.y)
			{
				(*itr)->SetStart(true);
				startFound = true;
			}
		}
		if(!startFound)
		{
			m_width *= 2;
			m_height *= 2;
		}
	}

	m_pathfinding->UpdateNodeList(m_nodes);

	m_path.clear();
	m_pathfinding->GetAStarPath(m_path);
	m_reached = false;
}


Seek::Seek(Framework* _framework, Pathfinding* _pathfinding, std::list<Node*> _nodes, AI* _AI, float _xSpace, float _ySpace)
{
	m_AI = _AI;
	m_pathfinding = _pathfinding;
	m_framework = _framework;
	m_nodes = _nodes;
	m_reached = false;
}

void Seek::Update(float dt)
{
	m_width = m_AI->GetSize().x;
	m_height = m_AI->GetSize().y;
	
	if(m_path.size() > 1)
	{
		m_AI->TurnTowards(m_path.front()->GetGlobalTransform().GetTranslation(), 10.0f);

		Vec2 shipTrans = m_AI->GetGlobalTransform().GetTranslation();
		Vec2 nodeTrans = m_path.front()->GetGlobalTransform().GetTranslation();

			if(	shipTrans.x - m_width < nodeTrans.x &&
				shipTrans.x + m_width > nodeTrans.x &&
				shipTrans.y - m_height < nodeTrans.y &&
				shipTrans.y + m_height > nodeTrans.y)
			m_path.pop_front();
	}
	else
		m_reached = true;
}

void Seek::Draw()
{
	if(m_AI->GetDrawPath())
	{
		if(m_path.size() > 0)
		{	
			m_framework->DrawLine(	m_AI->GetGlobalTransform().GetTranslation(), 
											m_path.front()->GetGlobalTransform().GetTranslation(), 
											Vec4(1, 0, 0, 1));
			for(auto node1 = m_path.begin(); node1 != m_path.end(); node1++)
			{
				(*node1)->SetColour(Vec4(0, 0, 1, 1));
					
				auto node2 = node1;
				node2++;
				if(node2 != m_path.end())
				{
					m_framework->DrawLine(	(*node1)->GetGlobalTransform().GetTranslation(), 
											(*node2)->GetGlobalTransform().GetTranslation(), 
											Vec4(1, 0, 0, 1));
				}
			}
		}
	}
}


void Seek::Reset()
{
	m_reached = false;
	m_width = m_AI->GetSize().x;
	m_height = m_AI->GetSize().y;

	m_path.clear();
	bool startFound = false;

	Vec2 shipTrans = m_AI->GetGlobalTransform().GetTranslation();
	while(!startFound)
	{
		for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
		{
			(*itr)->SetStart(false);
			(*itr)->SetFinish(false);
			(*itr)->SetOpen(false);
			(*itr)->SetParent(nullptr);
			(*itr)->m_GScore = 1;
			Vec2 nodeTrans = (*itr)->GetGlobalTransform().GetTranslation();

			if(	shipTrans.x - m_width < nodeTrans.x &&
				shipTrans.x + m_width > nodeTrans.x &&
				shipTrans.y - m_height < nodeTrans.y &&
				shipTrans.y + m_height > nodeTrans.y)
			{
				(*itr)->SetStart(true);
				startFound = true;
			}
		}
		if(!startFound)
		{
			m_width *= 2;
			m_height *= 2;
		}
	}
	m_pathfinding->GetDijkstrasPath(m_path);
	
}


