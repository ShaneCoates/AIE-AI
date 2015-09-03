#include "UI/Bar.h"	
#include "MathLib.h"
#include "Framework.h"

Bar::Bar(Framework* framework, Vec2 size, bool base) : SceneNode(framework)
{
	m_framework = framework;
	m_height = m_framework->GetSquareUnit() * size.y;

	m_percentage = 100;
	m_size		 =	size;
	m_width		 = m_size.x * (m_percentage / 100);
	m_sideWidth  = m_height * 0.5f;
	m_leftX		 =	-(m_height * 0.24f);
	m_rightX	 =	m_width + (m_height * 0.24f);


	if(base)
	{
		m_spriteCenter	= new Texture2D("resources/images/UI/UIfantasy32.png", true);	
		m_spriteLeft	= new Texture2D("resources/images/UI/UIfantasy31.png");	
		m_spriteRight	= new Texture2D("resources/images/UI/UIfantasy33.png");
	}
	else
	{
		m_spriteCenter	= new Texture2D("resources/images/UI/GreenTest.png", true);	
		m_spriteLeft	= new Texture2D("resources/images/UI/UIfantasy55.png");	
		m_spriteRight	= new Texture2D("resources/images/UI/UIfantasy07.png");
	}
	m_center = new SpriteSceneNode(m_framework, m_spriteCenter);
	m_left = new SpriteSceneNode(m_framework, m_spriteLeft);
	m_right = new SpriteSceneNode(m_framework, m_spriteRight);
	
	AddChild(m_center);
	AddChild(m_left);
	AddChild(m_right);
}


Bar::~Bar()
{

}

void Bar::Update(float dt)
{
	m_width		 =  (m_height * 0.25f) + (m_size.x * (m_percentage / 100));
	m_sideWidth  =  m_height * 0.5f;
	m_leftX		 =	0;
	m_rightX	 =	m_width * 1.01f;

	m_left->GetLocalTransform()->SetTranslation(Vec2(m_leftX, 0));
	m_right->GetLocalTransform()->SetTranslation(Vec2(m_rightX, 0));
	m_center->GetLocalTransform()->SetTranslation(Vec2(m_width * 0.5f, 0));

	m_center->SetUVCoordsInPixels(Vec4(0,  m_height, 0, m_width ));

	m_center->SetSize(Vec2(m_width, m_height));
	m_left->SetSize(Vec2(m_sideWidth, m_height));
	m_right->SetSize(Vec2(m_sideWidth, m_height));	
}

void Bar::Draw()
{	
	m_center->Draw();

	m_left->Draw();
	m_right->Draw();	

}

unsigned int Bar::GetPercentage()
{
	return m_percentage;
}

unsigned int Bar::GetPoint()
{
	return m_rightX;
}

void Bar::SetPoint(unsigned int point)
{
	m_rightX = point;
}

void Bar::SetPercentage(float per)
{
	m_percentage = per;
}

void Bar::SetOrange()
{
	m_center->SetTexture(new Texture2D("resources/images/UI/UIfantasy00.png", true));	
	m_left->SetTexture(new Texture2D("resources/images/UI/UIfantasy52.png"));	
	m_right->SetTexture(new Texture2D("resources/images/UI/UIfantasy04.png"));
}																		  
																		  
void Bar::SetBlue()														  
{																		  
	m_center->SetTexture(new Texture2D("resources/images/UI/UIfantasy01.png", true));	
	m_left->SetTexture(new Texture2D("resources/images/UI/UIfantasy53.png"));	
	m_right->SetTexture(new Texture2D("resources/images/UI/UIfantasy05.png"));
}																		 
																		 
void Bar::SetYellow()													 
{																		 
	m_center->SetTexture(new Texture2D("resources/images/UI/UIfantasy02.png", true));	
	m_left->SetTexture(new Texture2D("resources/images/UI/UIfantasy54.png"));	
	m_right->SetTexture(new Texture2D("resources/images/UI/UIfantasy06.png"));
}																		 
																		 
																		 
void Bar::SetGreen()													 
{																		 
	m_center->SetTexture(new Texture2D("resources/images/UI/UIfantasy03.png", true));	
	m_left->SetTexture(new Texture2D("resources/images/UI/UIfantasy55.png"));	
	m_right->SetTexture(new Texture2D("resources/images/UI/UIfantasy07.png"));
}