#include "UI/Label.h"
#include "UI/Box.h"
#include "Framework.h"

Label::Label(Framework* framework, Texture2D* pTexture, Vec2 boxSize) : SpriteSceneNode(framework, pTexture)
{
	m_Framework = framework;
	m_texture = pTexture;
	
	m_buttonSize = boxSize;

	m_minBounds = GetLocalTransform()->GetTranslation() - 40;
	m_maxBounds = GetLocalTransform()->GetTranslation() + m_buttonSize + 40;

	m_textPos = GetLocalTransform()->GetTranslation();
	m_textPos.y -= m_buttonSize.y * 0.5f;

	m_box = new Box(m_Framework, m_texture, Vec2(50, 50), m_buttonSize);
	AddChild(m_box);

	m_text = nullptr;
}

Label::~Label()
{
}

void Label::Update(float dt)
{
	m_textPos = GetGlobalTransform().GetTranslation();
	m_textPos.y -= m_buttonSize.y * 0.5f;

	m_minBounds = GetLocalTransform()->GetTranslation();
	m_minBounds.x -= 20;
	m_minBounds.y -= 20;

	m_maxBounds = GetLocalTransform()->GetTranslation() + m_buttonSize;
	m_maxBounds.x += 20;
	m_maxBounds.y += 20;


	m_box->Update(dt);

}

void Label::Draw()
{
	m_box->Draw();

	if(m_text != nullptr)
		m_Framework->DrawString("KenPixel16", m_text, m_textPos, Vec4(1.0f, 1.0f, 0.0f, 1.0f));


}

void Label::SetText(const char* text)
{
	m_text = text;
}