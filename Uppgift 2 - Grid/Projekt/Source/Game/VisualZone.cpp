#include "stdafx.h"
#include "VisualZone.h"
#include "tga2d/sprite/sprite.h"

VisualZone::VisualZone()
{
	mySprite = nullptr;
}

void VisualZone::Init(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aDim)
{
	myPosition.myX = aPos.x / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
	myPosition.myY = aPos.y / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
	myHitBox.Init({40*10,40*10}, aPos);
	mySprite = new Tga2D::CSprite("Sprites/Circle.dds");
	mySprite->SetColor({ 1,0,1,1 });
	mySprite->SetPosition({ aPos.x / Tga2D::CEngine::GetInstance()->GetWindowSize().x ,aPos.y / Tga2D::CEngine::GetInstance()->GetWindowSize().y });
	mySprite->SetPivot({ 0.5f,0.5f });
	mySprite->SetSizeRelativeToScreen({ 40.f / Tga2D::CEngine::GetInstance()->GetWindowSize().myX * Tga2D::CEngine::GetInstance()->GetWindowRatio(), 40.f / Tga2D::CEngine::GetInstance()->GetWindowSize().myY });
}

const Tga2D::Vector2f& VisualZone::GetPos()
{
	return myPosition;
}

const HitBox& VisualZone::GetHitbox()
{
	return myHitBox;
}

void VisualZone::Render()
{
	mySprite->Render();
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawCircle(myPosition, myHitBox.GetWidth() * 0.5f);
}
