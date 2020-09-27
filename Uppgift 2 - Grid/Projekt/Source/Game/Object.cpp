#include "stdafx.h"
#include "Object.h"
#include "tga2d/sprite/sprite.h"

void Object::Init(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aDim)
{
	myPosition = aPos;
	myHitBox.Init(aDim, aPos);
	mySprite = new Tga2D::CSprite("Sprites/Circle.dds");
	mySprite->SetPosition({aPos.x / Tga2D::CEngine::GetInstance()->GetWindowSize().x ,aPos.y / Tga2D::CEngine::GetInstance()->GetWindowSize().y});
	mySprite->SetSizeRelativeToScreen({ 40.f / Tga2D::CEngine::GetInstance()->GetWindowSize().myX* Tga2D::CEngine::GetInstance()->GetWindowRatio(), 40.f / Tga2D::CEngine::GetInstance()->GetWindowSize().myY });
}

void Object::Render()
{
	mySprite->Render();
}
