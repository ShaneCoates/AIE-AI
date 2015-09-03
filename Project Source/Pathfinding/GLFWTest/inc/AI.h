/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Base Entity class template

						All entity classes should roughly resemble
						the structure of this
-----------------------------------------------------------------------------*/

#ifndef AI_H
#define	AI_H

#include "framework\Framework.h"
#include "PhysicsObject.h"
class Texture2D;
class Pathfinding;
class Node;
class IAIState;
class Patrol;
class Target;
class Seek;

enum EState { PATROL, TARGET, SEEK };

class AI : public PhysicsObject
{
public:

	AI(Framework* framework, Texture2D* pTexture, std::list<Node*> _nodes, float _xSpace, float _ySpace);

	virtual ~AI();

	virtual void Update(float dt);
	virtual void Draw();

	void Reset();

	bool GetDrawPath()					{return m_drawPath;}
	void SetDrawPath(bool _setPath)		{m_drawPath = _setPath;}	

protected:
private:

	Pathfinding* m_pathfinding;
	Patrol* m_patrolState;
	Target* m_targetState;
	Seek* m_seekState;
	EState m_EState;
	bool m_drawPath;

};


#endif