#include "UI/Button.h"
#include "UI/Box.h"
#include "Framework.h"

Button::Button(Framework* framework, Texture2D* pTexture, Texture2D* pPressedTexture, Vec2 boxSize) : SpriteSceneNode(framework, pTexture)
{
	m_framework = framework;
	m_texture = pTexture;
	m_pressedTexture = pPressedTexture;
	m_buttonSize = boxSize;

	pressed = false;
	selected = false;
	btnDown = false;
	mouseOver = false;

	enabled = true;

	m_minBounds = GetGlobalTransform().GetTranslation() - 40;
	m_maxBounds = GetGlobalTransform().GetTranslation() + m_buttonSize + 40;

	m_textPos = GetGlobalTransform().GetTranslation();
	m_textPos.y -= m_buttonSize.y * 0.5f;

	m_box = new Box(m_framework, m_texture, Vec2(35, 35), m_buttonSize);
	AddChild(m_box);

	m_text = nullptr;
}

Button::~Button()
{
}

void Button::Update(float dt)
{
	m_textPos = GetGlobalTransform().GetTranslation();
	m_textPos.y -= m_buttonSize.y * 0.6f;

	m_mouseLocation = m_framework->GetMouseLocation();

	m_minBounds = GetGlobalTransform().GetTranslation();
	m_minBounds.x -= 20;
	m_minBounds.y -= 20;

	m_maxBounds = GetGlobalTransform().GetTranslation() + m_buttonSize;
	m_maxBounds.x += 20;

	if(enabled)
	{
		if(selected || mouseOver || pressed)
		{
			m_box->SetTexture(m_pressedTexture);
			m_textPos.y = GetGlobalTransform().GetTranslation().y - (m_buttonSize.y * 0.6f) - 4;

			pressed = (btnDown) ? true : false;
		}
		else
		{
			m_box->SetTexture(m_texture);
		}
	}
	CheckMousePos();

	m_box->Update(dt);

}

void Button::Draw()
{
	m_box->Draw();
	float alpha = (enabled) ? 1.0f : 0.3f;
	if(m_text != nullptr)
		m_framework->DrawString("KenPixelBlocks16", m_text, m_textPos, Vec4(1.0f, 1.0f, 1.0f, alpha));	

}

void Button::SetSelected(bool sel)
{
	selected = sel;
}

bool Button::GetPressed()
{
	if(enabled)
		return pressed;
	else
		return false;
}

bool Button::GetSelected()
{
	return selected;
}

void Button::SetControllerButtonDown(bool btn)
{
	btnDown = btn;
}

void Button::SetText(const char* text)
{
	m_text = text;
}

void Button::CheckMousePos()
{
	if(	m_mouseLocation.x < m_maxBounds.x &&
			m_mouseLocation.x > m_minBounds.x &&
			m_mouseLocation.y < m_maxBounds.y &&
			m_mouseLocation.y > m_minBounds.y)
	{
		mouseOver = (m_framework->GetMouseDown() || btnDown) ? false : true;
		pressed = !mouseOver;
	}
	else
		mouseOver = false;
}