#include "Framework/PathFinding.h"
#include "Node.h"
#include "Utils.h"

Pathfinding::Pathfinding(std::list<Node*> _nodes, float _xSpace, float _ySpace)
{
	m_nodes = _nodes;
	m_xSpacing = _xSpace;
	m_ySpacing = _ySpace;
}


void Pathfinding::GetDijkstrasPath(std::list<Node *> &outPath)
{
	Node*			 _currentNode = nullptr;
	std::list<Node*> _openList;

	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
	{
		if((*itr)->GetStart())
		{
			(*itr)->SetOpen(true);
			_openList.push_back(*itr);
			_currentNode = *itr;
			break;
		}
	}

	if(_currentNode == nullptr)
		return;

	while(!_currentNode->GetTarget() && _openList.size() > 0)
	{
		//create a list of neighbours
		std::list<Node*> _neighbours = _currentNode->GetNeighbours();
		//iterate through the neighbours and add them to the open list
		for(auto itr = _neighbours.begin(); itr != _neighbours.end(); itr++)
		{
			//check for a target
			if((*itr)->GetTarget())
			{
				(*itr)->SetParent(_currentNode);
				_currentNode = *itr;
				break;
			}

			//make sure it hasn't already been searched
			if((*itr)->GetParent() == nullptr)
			{
				//set each neighbour's 'open' variable to true
				(*itr)->SetOpen(true);
				//set each neighbour's parent
				(*itr)->SetParent(_currentNode);
				//set each neighbour's GScore
				(*itr)->m_GScore = (Vec2(	(*itr)->GetGlobalTransform().GetTranslation().x - (*itr)->GetParent()->GetGlobalTransform().GetTranslation().x,
											(*itr)->GetGlobalTransform().GetTranslation().y - (*itr)->GetParent()->GetGlobalTransform().GetTranslation().y).Length()
											+ (*itr)->m_GScore);
				//push the neighbour onto the open list
				_openList.push_back(*itr);
			}
		}	
		if(_currentNode->GetTarget())
			break;

		//set the current node to closed
		_currentNode->SetOpen(false);
		//remove the parent from the open list
		_openList.pop_front();

		
		if(_openList.size() < 1)
			break;
		
		//make sure the next node on the open list is still actually open
		while(!_openList.front()->GetOpen())
			_openList.pop_front();

		//sort the open list in terms of GScore
		_openList.sort( []( Node* const a, Node* const b)
		{
			return a->m_GScore > b->m_GScore;
		});

		//set the current node to be the next in the open list
		_currentNode = _openList.front();
		_currentNode->SetOpen(true);
	}

	if(_currentNode->GetTarget())
	{
		while(!_currentNode->GetStart())
		{
			outPath.push_front(_currentNode);
			_currentNode = _currentNode->GetParent();
		}
	}

	//clean up
	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
	{
		(*itr)->SetOpen(false);
	}


	return;
}

void Pathfinding::GetAStarPath(std::list<Node*> &outPath)
{
	Node*			 _currentNode = nullptr;
	Node*			 _endNode = nullptr;
	std::list<Node*> _openList;

	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
	{
		if((*itr)->GetStart())
		{
			(*itr)->SetOpen(true);
			_openList.push_back(*itr);
			_currentNode = *itr;
		}
		if((*itr)->GetFinish())
		{
			_endNode = *itr;
		}
	}

	if(_currentNode == nullptr || _endNode == nullptr)
		return;


	float _dx1;
	float _dy1;
	float _dx2 = _currentNode->m_xPos - _endNode->m_xPos;
	float _dy2 = _currentNode->m_yPos - _endNode->m_yPos;
	float _cross;

	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
	{
		_dx1 = (*itr)->m_xPos - _endNode->m_xPos;
		_dy1 = (*itr)->m_yPos - _endNode->m_yPos;
		_cross = abs(_dx1*_dy2 - _dx2*_dy1);
		(*itr)->m_HScore = _cross * 0.001;
	}

	if(_currentNode == nullptr)
		return;

	while(!_currentNode->GetFinish() && _openList.size() > 0)
	{
		//create a list of neihbours
		std::list<Node*> _neighbours = _currentNode->GetNeighbours();
		//iterate through the neighbours and add them to the open list
		for(auto itr = _neighbours.begin(); itr != _neighbours.end(); itr++)
		{
			//check for a target
			if((*itr)->GetFinish())
			{
				(*itr)->SetParent(_currentNode);
				_currentNode = *itr;
				break;
			}

			//make sure it hasn't already been searched
			if((*itr)->GetParent() == nullptr)
			{
				//set each neighbour's 'open' variable to true
				(*itr)->SetOpen(true);
				//set each neighbour's parent
				(*itr)->SetParent(_currentNode);
				//set each neighbour's GScore
				(*itr)->m_GScore = ((*itr)->GetParent()->m_GScore + (*itr)->m_GScore);
				//push the neighbour onto the open list
				_openList.push_back(*itr);

			}
		}	
		if(_currentNode->GetFinish())
			break;

		//set the current node to closed
		_currentNode->SetOpen(false);
		//remove the parent from the open list
		_openList.pop_front();

		if(_openList.size() <= 1)
			break;
		else
		{
			//make sure the next node on the open list is still actually open
			while(!_openList.front()->GetOpen())
				_openList.pop_front();

			//sort the open list in terms of GScore
			_openList.sort( []( Node* const a, Node* const b)
			{
				return (a->m_HScore + a->m_GScore) < (b->m_HScore + b->m_GScore);
			});

			//set the current node to be the next in the open list
			_currentNode = _openList.front();
			_currentNode->SetOpen(true);
		}
	}

	if(_currentNode->GetFinish() && !_currentNode->GetStart())
	{
		outPath.push_back(_currentNode);
		while(!_currentNode->GetParent()->GetStart())
		{
			outPath.push_front(_currentNode);
			_currentNode = _currentNode->GetParent();
		}
		outPath.push_front(_currentNode);
		outPath.push_front(_currentNode->GetParent());

	}
	//clean up
	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
	{
		(*itr)->SetOpen(false);
	}

	return;
}

void Pathfinding::UpdateNodeList(std::list<Node*> _nodes)
{
	m_nodes.clear();
	m_nodes = _nodes;
}

void Pathfinding::ResetEndNode()
{
	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
	{
		(*itr)->SetFinish(false);
	}

	auto finishNode = m_nodes.begin();
	unsigned int rand = Utils::RandomNumber(0, m_nodes.size() - 1);
	for(int i = 0; i < rand; i++)
		finishNode++;

	(*finishNode)->SetFinish(true);
}

void Pathfinding::ResetDijkstraPoints(unsigned int _points)
{
	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
		(*itr)->SetTarget(false);

	unsigned int targets = 0;
	while(targets < _points)
	{
		auto targetNode = m_nodes.begin();
		float rand = Utils::RandomNumber(0, m_nodes.size() - 1);
		for(int i = 0; i < rand; i++)
			targetNode++;

		(*targetNode)->SetTarget(true);
		targets++;
	}
}

void Pathfinding::FindNodeInRange(Vec2 _pos, float _range, std::list<Node*> &outNodes)
{
	//pre-define some variables for readability
	float _minX = _pos.x - _range;
	float _maxX = _pos.x + _range;
	float _minY = _pos.y - _range;
	float _maxY = _pos.y + _range;

	//search through all nodes in the list
	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
	{
		//check to see if the node is in range
		if((*itr)->GetGlobalTransform().GetTranslation().x > _minX &&
           (*itr)->GetGlobalTransform().GetTranslation().x < _maxX &&
           (*itr)->GetGlobalTransform().GetTranslation().y > _minY &&
           (*itr)->GetGlobalTransform().GetTranslation().y < _maxY)
		outNodes.push_back(*itr);
   }
}

void Pathfinding::SetFinish(Vec2 _pos, float _range)
{
	std::list<Node*> _selectedNodes;
	FindNodeInRange(_pos,_range, _selectedNodes);
	for(auto itr = m_nodes.begin(); itr != m_nodes.end(); itr++)
		(*itr)->SetFinish(false);
	if(_selectedNodes.size() > 0)
		_selectedNodes.front()->SetFinish(true);
}