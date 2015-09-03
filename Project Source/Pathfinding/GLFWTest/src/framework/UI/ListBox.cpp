#include "UI/ListBox.h"
#include "Framework.h"
#include <tinyxml2.h>


using namespace AIE;
using namespace std;
using namespace tinyxml2;

ListBox::ListBox(Framework* framework, Vec2 boxSize, char* title, std::string fileName) : SceneNode(framework)
{
	m_framework = framework;

	m_boxSize = boxSize;
	m_fileName = fileName;

	m_topTexture		= new Texture2D("resources/images/UI/dropdownTop.png", true);
	m_centerTexture		= new Texture2D("resources/images/UI/dropdownMid.png", true);
	m_bottomTexture		= new Texture2D("resources/images/UI/dropdownBottom.png", true);
	m_seperatorTexture	= new Texture2D("resources/images/UI/grey_sliderHorizontal.png", true);

	Box* m_topBox = new Box(m_framework, m_topTexture, Vec2(50, 15) , m_boxSize);
	//m_topBox->SetText(title);
	m_boxes.push_back(m_topBox);
	
	AddChild(m_topBox);

	m_position = Vec2(0, 0);

	LoadItems();
	CalculatePositions();
	open = false;
}

ListBox::~ListBox()
{
	delete m_topTexture;
	delete m_centerTexture;	
	delete m_bottomTexture;	
	delete m_seperatorTexture;

	for(auto itr = m_boxes.begin(); itr != m_boxes.end(); ++itr)
	{
		delete (*itr);
		itr = m_boxes.erase(itr);
	}
}


void ListBox::Update(float dt)
{
	for(auto itr = m_Children.begin(); itr != m_Children.end(); ++itr)
	{
		(*itr)->Update(dt);
	}

}
void ListBox::Draw()
{


	if(!open)
		m_boxes.front()->Draw();
	else
	{
		for(auto itr = m_Children.begin(); itr != m_Children.end(); ++itr)
		{
			(*itr)->Draw();
		}
	}
}

void ListBox::LoadItems()
{
	tinyxml2::XMLDocument doc;
	
	if(doc.LoadFile(m_fileName.c_str()) == XML_SUCCESS)
	{
		auto element = doc.FirstChildElement("Player")->FirstChildElement();
		while(element != NULL)
		{
			Box* currBox = new Box(m_framework, m_centerTexture, Vec2(50, 15), m_boxSize);
			Box* currSeperator = new Box(m_framework, m_seperatorTexture, Vec2(5, 5), Vec2(m_boxSize.x, 5));
			string currString = element->Attribute("Name");
			m_list.push_back(currString);
			//currBox->SetText(currString.c_str());
			m_boxes.push_back(currBox);
			m_seperators.push_back(currSeperator);

			AddChild(currSeperator);
			AddChild(currBox);
			
			element = element->NextSiblingElement();
		}

		m_boxes.back()->SetTexture(m_bottomTexture);
	}
	
}

void ListBox::CalculatePositions()
{
	Vec2 position = m_position;

	for(auto itr = m_boxes.begin(); itr != m_boxes.end(); itr++)
	{
		position.y -= m_boxSize.y;

		m_positions.push_back(position);
		(*itr)->GetLocalTransform()->SetTranslation(position);
	}
	position = m_position;
	for(auto itr = m_seperators.begin(); itr != m_seperators.end(); itr++)
	{
		position.y -= m_boxSize.y;

		m_positions.push_back(position);
		(*itr)->GetLocalTransform()->SetTranslation(position);
	}

}