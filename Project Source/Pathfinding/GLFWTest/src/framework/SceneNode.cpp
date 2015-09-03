#include "SceneNode.h"

SceneNode::SceneNode(Framework *framework) : m_Framework(framework)
{
	m_Parent = nullptr;
	m_LocalTransform = Mat3x3();
}

SceneNode::~SceneNode()
{
	for(auto itr = m_Children.begin(); itr != m_Children.end(); ++itr)
	{
		//(*itr)->m_Parent = nullptr;
	}

	m_Children.clear();
}

void SceneNode::AddChild(SceneNode *child)
{
	if(child->m_Parent != nullptr)
	{
		child->m_Parent->RemoveChild(child);
	}

	child->m_Parent = this;
	m_Children.push_back(child);
}

void SceneNode::RemoveChild(SceneNode *child)
{
	for(auto itr = m_Children.begin(); itr != m_Children.end(); ++itr)
	{
		if(*itr == child)
		{
			child->m_Parent = nullptr;
			m_Children.erase(itr);
			break;
		}
	}
}

void SceneNode::Update(float deltaTime)
{
	for(auto itr = m_Children.begin(); itr != m_Children.end(); ++itr)
	{
		(*itr)->Update(deltaTime);
	}

}
void SceneNode::Draw()
{
	for(auto itr = m_Children.begin(); itr != m_Children.end(); ++itr)
	{
		(*itr)->Draw();
	}
}

Mat3x3 SceneNode::GetGlobalTransform()
{
	if(m_Parent == nullptr) return m_LocalTransform;

	return m_LocalTransform * m_Parent->GetGlobalTransform();
}

