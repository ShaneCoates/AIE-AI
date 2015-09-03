/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Node class
						
-----------------------------------------------------------------------------*/

#ifndef NODE_H
#define	NODE_H

#include "framework\Framework.h"
#include "framework\Texture2D.h"
#include "SpriteSceneNode.h"
#include <list>




class Node : public SceneNode
{
public:

	Node(Framework* framework, Vec2 position);

	virtual ~Node();

	virtual void Update(float dt);
	virtual void Draw();

	//Pathfinding getters and setters

	float				GetCost()			{return	m_cost;}
	bool				GetOpen()			{return m_open;}
	bool				GetTarget()			{return m_target;}
	bool				GetFinish()			{return m_finish;}
	bool				GetStart()			{return m_start;}
	Node*				GetParent()			{return m_parent;}
	std::list<Node*>	GetNeighbours()		{return m_neighbours;}


	void SetCost(float _cost)				{m_cost = _cost;}
	void SetOpen(bool _open)				{m_open = _open;}
	void SetTarget(bool _target)			{m_target = _target;}
	void SetStart(bool _start)				{m_start = _start;}
	void SetFinish(bool _finish)			{m_finish = _finish;}
	void SetParent(Node* _parent)			{m_parent = _parent;}
	void AddNeighbours(Node* _neighbor)		{m_neighbours.push_back(_neighbor);}
	void ClearNeighbours()					{m_neighbours.clear();}
	void SetColour(const Vec4& _colour)		{m_colour = _colour;}

	float	m_GScore;
	float	m_HScore;

	float	m_xPos;
	float	m_yPos;

protected:
private:

	Vec4	m_colour;

	//Pathfinding Variables
	float	m_cost;
	bool	m_open;
	bool	m_target;
	bool	m_start;
	bool	m_finish;
	Node*	m_parent;
	std::list<Node*> m_neighbours;

};


#endif