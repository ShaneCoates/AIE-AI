#include "Framework.h"
#include "Texture2D.h"
#include "SpriteSceneNode.h"

SpriteSceneNode::SpriteSceneNode(Framework *framework, Texture2D *texture)
	: SceneNode(framework)
{
	m_Texture = texture;
	m_UVCoords = Vec4(0.0f,1.0f, 0.0f, 1.0f);
	m_size = Vec2(m_Texture->GetWidth(), m_Texture->GetHeight());
	m_centered = false;
	m_colour = Vec4(1, 1, 1, 1);
}

SpriteSceneNode::~SpriteSceneNode()
{

}

void SpriteSceneNode::SetTextureScaleTransformInPixels(const Vec2& scale)
{
	m_LocalTransform.SetScale
	(
	Vec2
	(
		scale.x / (float)m_Texture->GetWidth(),
		scale.y / (float)m_Texture->GetHeight()
	)
	);
}

void SpriteSceneNode::SetUVCoords(const Vec4& UV)
{
	m_UVCoords = UV;
	//Vec2 scale = Vec2(UV.w - UV.z, UV.y - UV.x);
	
	//GetGlobalTransform()->SetScale(Vec2(UV.w - UV.z, UV.y - UV.x));
}

void SpriteSceneNode::SetUVCoordsInPixels(const Vec4& UV)
{
	SetUVCoords(
		Vec4(	UV.x / m_Texture->GetHeight(),
					UV.y / m_Texture->GetHeight(),
					UV.z / m_Texture->GetWidth(),
					UV.w / m_Texture->GetWidth())
				);
	
}

void SpriteSceneNode::SetSize(const Vec2& scale)
{
	m_size = scale;
}

Vec2 SpriteSceneNode::GetSize()
{
	return m_size;
}

void SpriteSceneNode::Draw()
{
	m_Framework->SetColour(m_colour);
	m_Framework->DrawSprite(m_Texture, m_size, GetGlobalTransform(), m_centered, m_UVCoords);
	SceneNode::Draw();
	m_Framework->SetColour(Vec4(1, 1, 1, 1));
	//m_UVCoords = Vec4(0.0f,1.0f, 0.0f, 1.0f);
}

unsigned int SpriteSceneNode::GetWidth() 
{ 
	return m_Texture->GetWidth();
}

unsigned int SpriteSceneNode::GetHeight() 
{
	return m_Texture->GetHeight();
}

bool SpriteSceneNode::GetMouseOver()
{
	Vec2 minBounds = GetGlobalTransform().GetTranslation();
	Vec2 maxBounds = GetGlobalTransform().GetTranslation() + GetSize();
	Vec2 mousePos = m_Framework->GetMouseLocation();

	if(	mousePos.x >= minBounds.x &&
		mousePos.y >= minBounds.y &&
		mousePos.x <= maxBounds.x &&
		mousePos.y <= maxBounds.y)
		return true;
	return false;
		

}