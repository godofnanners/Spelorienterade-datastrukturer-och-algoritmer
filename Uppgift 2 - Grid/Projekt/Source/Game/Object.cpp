#include "stdafx.h"
#include "Object.h"
#include "tga2d/sprite/sprite.h"

void Object::Init(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aDim)
{
	myPosition = aPos;
	myHitBox.Init(aDim, aPos);
	mySprite = new Tga2D::CSprite("Sprites/Circle.dds");
	mySprite->SetPivot({ 0.5f,0.5f });
	myColor = { 1,1,1,0.5f };
}

void Object::SetAlpha(float aAlpha)
{
	myColor = { myColor.myR,myColor.myG,myColor.myB,aAlpha };
}

void Object::SetColor(Tga2D::CColor aColor)
{
	myColor = aColor;
}

void Object::SetPos(const Tga2D::Vector2f& aPosition)
{
	myPosition = aPosition;
	myHitBox.Init({ 40,40 }, aPosition);
}

void Object::Render()
{
	myHitBox.DrawHitbox();
	mySprite->SetColor(myColor);
	mySprite->SetPosition({ myPosition.x / Tga2D::CEngine::GetInstance()->GetWindowSize().x ,myPosition.y / Tga2D::CEngine::GetInstance()->GetWindowSize().y });
	mySprite->SetSizeRelativeToScreen({ 40.f / Tga2D::CEngine::GetInstance()->GetWindowSize().myX * Tga2D::CEngine::GetInstance()->GetWindowRatio(), 40.f / Tga2D::CEngine::GetInstance()->GetWindowSize().myY });
	mySprite->Render();
}
Tga2D::Vector2f Object::GetPos()
{
	return myPosition;
}

const HitBox& Object::GetHitbox()
{
	return myHitBox;
}
