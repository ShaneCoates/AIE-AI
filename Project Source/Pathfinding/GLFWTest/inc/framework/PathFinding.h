// Author: Shane Coates
// Description: Pathfinding functions

#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <list>

class Node;
class Vec2;

class Pathfinding
{
public:

	Pathfinding(std::list<Node*> _nodes, float _xSpace, float _ySpace);

	void GetDijkstrasPath(std::list<Node*> &outPath);
	void GetAStarPath(std::list<Node*> &outPath);

	void UpdateNodeList(std::list<Node*> _nodes);
	void ResetEndNode();
	void ResetDijkstraPoints(unsigned int _points);

	void FindNodeInRange(Vec2 _pos, float _range, std::list<Node*> &outNodes);
	void SetFinish(Vec2 _pos, float _range);

private:
	std::list<Node*> m_nodes;
	float m_xSpacing;
	float m_ySpacing;
};

#endif

