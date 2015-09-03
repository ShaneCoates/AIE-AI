//#include "UI/Slider.h"	
//#include "UI/Bar.h"
//#include "MathLib.h"
//#include "Framework.h"
//
//Slider::Slider(Framework* framework, Vec2 size) : SceneNode(framework)
//{
//	m_barSize = size;
//	m_modifiable = false;
//
//	m_pointerTexture = new Texture2D("resources/images/spritesheet/greySheet.png", true);
//	m_pointer = new SpriteSceneNode(framework, m_pointerTexture);
//	m_pointer->SetUVCoordsInPixels(m_Framework->GetUVGrey("grey_sliderUp.png", m_pointerTexture));
//
//	m_pointer->GetLocalTransform()->SetTranslation(Vec2(0, 0));
//	m_pointer->SetSize(Vec2(m_Framework->GetSquareUnit(), m_Framework->GetSquareUnit() * 2));
//
//	m_baseBar = new Bar(framework, m_barSize, true);
//	m_bar = new Bar(framework, m_barSize);
//
//
//	AddChild(m_baseBar);
//	AddChild(m_bar);
//	AddChild(m_pointer);
//}
//
//Slider::~Slider()
//{
//}
//
//void Slider::Update(float dt)
//{
//	m_baseBar->Update(dt);
//	m_bar->Update(dt);
//	m_pointer->GetLocalTransform()->SetTranslation(Vec2(m_bar->GetPoint(), 10));
//	m_pointer->Update(dt);	
//	CheckInput();
//
//}
//
//unsigned int Slider::GetPercentage()
//{
//	return m_bar->GetPercentage();
//}
//
//void Slider::SetPercentage(float per)
//{
//	m_bar->SetPercentage(per);
//}
//
//void Slider::SetOrange()
//{
//	m_bar->SetOrange();
//}
//	
//void Slider::SetBlue()
//{
//	m_bar->SetBlue();
//}
//
//void Slider::SetYellow()
//{
//	m_bar->SetYellow();
//}
//
//void Slider::SetGreen()
//{
//	m_bar->SetGreen();
//}
//
//void Slider::SetModifiable(bool modify)
//{
//	m_modifiable = modify;
//}
//
//void Slider::CheckInput()
//{
//	m_mouseLocation = m_Framework->GetMouseLocation() - m_bar->GetGlobalTransform().GetTranslation();
//
//	m_minBounds = GetLocalTransform()->GetTranslation();
//	m_minBounds.x -= 20;
//	m_minBounds.y -= 20;
//
//	m_maxBounds = GetLocalTransform()->GetTranslation() + m_barSize;
//	m_maxBounds.x += 20;
//
//	if(	m_mouseLocation.x < m_maxBounds.x &&
//			m_mouseLocation.x > m_minBounds.x &&
//			m_mouseLocation.y < m_maxBounds.y &&
//			m_mouseLocation.y > m_minBounds.y &&
//			m_Framework->GetMouseDown())
//				m_bar->SetPoint(m_mouseLocation.x);
//}