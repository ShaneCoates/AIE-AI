/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Scene Node

-----------------------------------------------------------------------------*/


#ifndef SCENENODE_H
#define	SCENENODE_H

#include <list>
#include <MathLib.h>

class Framework;

class SceneNode
{
public:
	SceneNode(Framework *framework);
	virtual ~SceneNode();

	void AddChild(SceneNode *child);
	void RemoveChild(SceneNode *child);

	virtual void Update(float deltaTime);
	virtual void Draw();

	Mat3x3 GetGlobalTransform();
	inline Mat3x3 *GetLocalTransform() {return &m_LocalTransform; }

protected:

	SceneNode* m_Parent;
	std::list<SceneNode *> m_Children;
	Framework *m_Framework;

	Mat3x3 m_LocalTransform;
};


#endif