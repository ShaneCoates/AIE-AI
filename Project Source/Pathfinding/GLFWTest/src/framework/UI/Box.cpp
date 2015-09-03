#include "UI/Box.h"
#include "Framework.h"
#include "Texture2D.h"

Box::Box(Framework* framework, Texture2D* pTexture, Vec2 UVSize, Vec2 boxSize) : SpriteSceneNode(framework, pTexture)
{
	m_UVSize = UVSize;
	m_boxSize = boxSize;

	m_Texture = pTexture;
	m_Framework = framework;

	TopLeft = new SpriteSceneNode(framework, pTexture);		AddChild(TopLeft);
	Top = new SpriteSceneNode(framework, pTexture);			AddChild(Top);
	TopRight = new SpriteSceneNode(framework, pTexture);	AddChild(TopRight);
	
	Left = new SpriteSceneNode(framework, pTexture);		AddChild(Left);
	Center = new SpriteSceneNode(framework, pTexture);		AddChild(Center);
	Right = new SpriteSceneNode(framework, pTexture);		AddChild(Right);
	
	BottomLeft = new SpriteSceneNode(framework, pTexture);	AddChild(BottomLeft);
	Bottom = new SpriteSceneNode(framework, pTexture);		AddChild(Bottom);
	BottomRight = new SpriteSceneNode(framework, pTexture);	AddChild(BottomRight);

	SetSize();
}

Box::~Box()
{
	
}

void Box::Update(float dt)
{
	SetBoxTexture(m_Texture);
	
	SetPositions();
	SetUVs();
	SetSize();

}

void Box::Draw()
{	
	
	Top->Draw();
	Left->Draw();
	Center->Draw();
	Right->Draw();
	Bottom->Draw();

	TopLeft->Draw();
	TopRight->Draw();
	BottomLeft->Draw();
	BottomRight->Draw();
}

void Box::SetSize()
{

	m_xPos[0] = 0;
	m_xPos[1] = m_UVSize.x;
	m_xPos[2] = m_Texture->GetWidth() - m_UVSize.x;
	m_xPos[3] = m_Texture->GetWidth();

	m_yPos[0] = 0;
	m_yPos[1] = m_UVSize.y;
	m_yPos[2] = m_Texture->GetHeight() - m_UVSize.y;
	m_yPos[3] = m_Texture->GetHeight();

	m_sideY = m_boxSize.y / (m_Texture->GetHeight());
	m_topX = m_boxSize.x / (m_Texture->GetWidth());


	Top->GetLocalTransform()->SetScale(Vec2(m_topX, 1.0f));
	Bottom->GetLocalTransform()->SetScale(Vec2(m_topX, 1.0f));

	Center->GetLocalTransform()->SetScale(Vec2(m_topX, m_sideY));

	Right->GetLocalTransform()->SetScale(Vec2(1.0f, m_sideY));
	Left->GetLocalTransform()->SetScale(Vec2(1.0f, m_sideY));



}

void Box::SetUVs()
{
	TopLeft->SetUVCoordsInPixels	(Vec4(m_yPos[0], m_yPos[1], m_xPos[0], m_xPos[1]));
	Top->SetUVCoordsInPixels		(Vec4(m_yPos[0], m_yPos[1], m_xPos[1], m_xPos[2]));
	TopRight->SetUVCoordsInPixels	(Vec4(m_yPos[0], m_yPos[1], m_xPos[2], m_xPos[3]));

	Left->SetUVCoordsInPixels		(Vec4(m_yPos[1], m_yPos[2], m_xPos[0], m_xPos[1]));
	Center->SetUVCoordsInPixels		(Vec4(m_yPos[1], m_yPos[2], m_xPos[1], m_xPos[2]));
	Right->SetUVCoordsInPixels		(Vec4(m_yPos[1], m_yPos[2], m_xPos[2], m_xPos[3]));

	BottomLeft->SetUVCoordsInPixels	(Vec4(m_yPos[2], m_yPos[3], m_xPos[0], m_xPos[1]));			
	Bottom->SetUVCoordsInPixels		(Vec4(m_yPos[2], m_yPos[3], m_xPos[1], m_xPos[2]));			
	BottomRight->SetUVCoordsInPixels(Vec4(m_yPos[2], m_yPos[3], m_xPos[2], m_xPos[3]));			
}

void Box::SetPositions()
{
	BottomLeft->GetLocalTransform()->SetTranslation(::Vec2(0, m_boxSize.y));
	Bottom->GetLocalTransform()->SetTranslation(Vec2(m_boxSize.x * 0.5f, m_boxSize.y));
	BottomRight->GetLocalTransform()->SetTranslation(m_boxSize);
		
	Left->GetLocalTransform()->SetTranslation(Vec2(0, m_boxSize.y * 0.5f));
	Center->GetLocalTransform()->SetTranslation(Vec2(m_boxSize.x * 0.5f, m_boxSize.y * 0.5f));
	Right->GetLocalTransform()->SetTranslation(Vec2(m_boxSize.x, (m_boxSize.y * 0.5f)));
		
	TopLeft->GetLocalTransform()->SetTranslation(Vec2(0, 0));
	Top->GetLocalTransform()->SetTranslation(Vec2(m_boxSize.x * 0.5f, 0));
	TopRight->GetLocalTransform()->SetTranslation(Vec2(m_boxSize.x, 0));
}

void Box::SetBoxSize(Vec2 size)
{
	m_boxSize = size;
}

void Box::SetBoxTexture(Texture2D* tex)
{
	TopLeft->SetTexture(tex);
	Top->SetTexture(tex);
	TopRight->SetTexture(tex);
	
	Left->SetTexture(tex);
	Center->SetTexture(tex);
	Right->SetTexture(tex);
	
	BottomLeft->SetTexture(tex);
	Bottom->SetTexture(tex);
	BottomRight->SetTexture(tex);
}
