#include "stdafx.h"
#include "HitBox.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/engine.h>

HitBox::HitBox()
{
	myWidth = 0;
	myHeight = 0;
	myPos = { 0,0 };
}

void HitBox::Init(Tga2D::CSprite* aSprite)
{
	myWidth = aSprite->GetSize().x;
	myHeight = aSprite->GetSize().y;
	myPos = aSprite->GetPosition();
	myPivot = aSprite->GetPivot();
}

void HitBox::Init(const Tga2D::Vector2f& aDim,const Tga2D::Vector2f& aPos)
{
	myWidth = aDim.x;
	myHeight = aDim.y;
	myPos.x = aPos.x;
	myPos.y = aPos.y;
}

const Tga2D::Vector2f HitBox::GetPos()
{
	return myPos;
}

const float HitBox::GetWidth()
{
	return myWidth;
}

const float HitBox::GetHeight()
{
	return myHeight;
}

void HitBox::Update(Tga2D::Vector2f aPosition)
{
	myPos = aPosition;
	//DrawHitbox();
}

void HitBox::DrawHitbox(Tga2D::CColor aColor) const
{
	Tga2D::Vector2f pos = { myPos.x / Tga2D::CEngine::GetInstance()->GetWindowSize().x, myPos.x / Tga2D::CEngine::GetInstance()->GetWindowSize().y };
	float width=myWidth/ Tga2D::CEngine::GetInstance()->GetWindowSize().x;
	float height = myHeight / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Tga2D::Vector2f(pos.x + width,pos.y + height), Tga2D::Vector2f(pos.x + width, pos.y), aColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Tga2D::Vector2f(pos.x, pos.y + height), pos, aColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Tga2D::Vector2f(pos.x + width, pos.y), pos, aColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Tga2D::Vector2f(pos.x, pos.y + height), Tga2D::Vector2f(pos.x + width, pos.y + height), aColor);
}

bool HitBox::CheckCollision(HitBox aHitbox) const
{
	if (myPos.x<aHitbox.GetPos().x+(aHitbox.GetWidth()) &&
		myPos.x + myWidth > aHitbox.GetPos().x &&
		myPos.y < aHitbox.GetPos().y + (aHitbox.GetHeight()) &&
		myPos.y + (myHeight) > aHitbox.GetPos().y)
	{
       		return true;
	}
	return false;
}

bool HitBox::CheckifPointIsInside(Tga2D::Vector2f aPoint) const
{
	if (aPoint.x > myPos.x  && aPoint.x < myPos.x+myWidth && aPoint.y > myPos.y && aPoint.y < myPos.y+myHeight)
	{
		return true;
	}

	return false;
}