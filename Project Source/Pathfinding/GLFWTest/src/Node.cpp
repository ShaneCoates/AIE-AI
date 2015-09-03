#include "Node.h"
#include "Framework.h"


Node::Node(Framework* framework, Vec2 position) : SceneNode(framework)
{
	m_Framework = framework;
	m_colour	= Vec4(1, 1, 1, 1);
	m_cost		= 0;
	m_GScore	= 0;
	m_open		= false;
	m_parent	= nullptr;
	m_target	= false;
	m_start		= false;
	m_finish	= false;

	GetLocalTransform()->SetTranslation(position);
	GetLocalTransform()->SetScale(5, 5);

	m_xPos = GetGlobalTransform().GetTranslation().x;
	m_yPos = GetGlobalTransform().GetTranslation().y;

}

Node::~Node()
{

}

void Node::Update(float dt)
{

	if(m_xPos != GetGlobalTransform().GetTranslation().x)
		m_xPos = GetGlobalTransform().GetTranslation().x;
	if(m_yPos != GetGlobalTransform().GetTranslation().y)
		m_yPos = GetGlobalTransform().GetTranslation().y;

	if(m_target)
		SetColour(Vec4(1, 1, 0, 1));

	if(!m_start && !m_finish && !m_target)
		SetColour(Vec4(1, 1, 1, 1));
	
}

void Node::Draw()
{
	//if(m_target)
		m_Framework->DrawQuad(GetGlobalTransform(), true, m_colour);
}
