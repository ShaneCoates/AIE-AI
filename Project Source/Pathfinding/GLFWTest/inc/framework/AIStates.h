#ifndef AISTATE_H
#define	AISTATE_H


#include "Framework.h"
#include "MathLib.h"
#include <list>
#include "Node.h"
#include "AI.h"
#include "PathFinding.h"

class IAIState
{
public:

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;

protected:
private:
};

class Patrol : public IAIState
{
public:

	Patrol(Framework* _framework, Pathfinding* _pathfinding, std::list<Node*> _nodes, AI* _AI, float _xSpace, float _ySpace);
	virtual void Update(float dt);
	virtual void Draw();
	void Reset();
private:

	std::list<Node*> m_nodes;
	std::list<Node*> m_path;

	AI* m_AI;
	Pathfinding* m_pathfinding;
	Framework* m_framework;
};

class Target : public IAIState
{
public:

	Target(Framework* _framework, Pathfinding* _pathfinding, std::list<Node*> _nodes, AI* _AI, float _xSpace, float _ySpace);
	virtual void Update(float dt);
	virtual void Draw();

	void UpdateTarget(Vec2 _pos, float _range);
	void Reset();
	bool IsReached()			{return m_reached;}
private:

	std::list<Node*> m_nodes;
	std::list<Node*> m_path;

	AI* m_AI;
	Pathfinding* m_pathfinding;
	Framework* m_framework;
	float m_width;
	float m_height;

	bool m_reached;
};


class Seek : public IAIState
{
public:

	Seek(Framework* _framework, Pathfinding* _pathfinding, std::list<Node*> _nodes, AI* _AI, float _xSpace, float _ySpace);
	virtual void Update(float dt);
	virtual void Draw();

	void Reset();
	bool IsReached()			{return m_reached;}

private:

	std::list<Node*> m_nodes;
	std::list<Node*> m_path;

	AI* m_AI;
	Pathfinding* m_pathfinding;
	Framework* m_framework;
	float m_width;
	float m_height;
	bool m_reached;
};


#endif