#include "stdafx.h"
#include "VisualZone.h"
#include "tga2d/sprite/sprite.h"

VisualZone::VisualZone()
{
	mySprite = nullptr;
}

void VisualZone::Init(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aDim)
{
	myPosition = aPos;
	myHitBox.Init({ 40 * 10,40 * 10 }, aPos);
	mySprite = new Tga2D::CSprite("Sprites/Circle.dds");
	mySprite->SetColor({ 1,0,1,1 });
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
	mySprite->SetPosition({ myPosition.x / Tga2D::CEngine::GetInstance()->GetWindowSize().x ,myPosition.y / Tga2D::CEngine::GetInstance()->GetWindowSize().y });
	mySprite->SetPivot({ 0.5f,0.5f });
	mySprite->SetSizeRelativeToScreen({ 40.f / Tga2D::CEngine::GetInstance()->GetWindowSize().myX * Tga2D::CEngine::GetInstance()->GetWindowRatio(), 40.f / Tga2D::CEngine::GetInstance()->GetWindowSize().myY });
	mySprite->Render();
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawCircle({ myPosition.x / Tga2D::CEngine::GetInstance()->GetWindowSize().myX,myPosition.y / Tga2D::CEngine::GetInstance()->GetWindowSize().myY }, myHitBox.GetWidth() / Tga2D::CEngine::GetInstance()->GetWindowSize().x * 0.5f);
}
