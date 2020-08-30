#include "stdafx.h"
#include "HitBox.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/engine.h>

HitBox::HitBox()
{
	myWidth = 0;
	myHeight = 0;
	myCenterPosition = { 0,0 };
}

void HitBox::Init(Tga2D::CSprite* aSprite)
{
	myWidth = aSprite->GetSize().x/Tga2D::CEngine::GetInstance()->GetWindowRatio();
	myHeight = aSprite->GetSize().y;
	myCenterPosition = aSprite->GetPosition();
	myPivot = aSprite->GetPivot();
}

const Tga2D::Vector2f HitBox::GetPos()
{
	return myCenterPosition;
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
	myCenterPosition = aPosition;
	//DrawHitbox();
}

void HitBox::DrawHitbox(Tga2D::CColor aColor)
{
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Tga2D::Vector2f(myCenterPosition.x + myWidth, myCenterPosition.y + myHeight), Tga2D::Vector2f(myCenterPosition.x + myWidth, myCenterPosition.y), aColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Tga2D::Vector2f(myCenterPosition.x, myCenterPosition.y + myHeight), myCenterPosition, aColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Tga2D::Vector2f(myCenterPosition.x + myWidth, myCenterPosition.y), myCenterPosition, aColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine(Tga2D::Vector2f(myCenterPosition.x, myCenterPosition.y + myHeight), Tga2D::Vector2f(myCenterPosition.x + myWidth, myCenterPosition.y + myHeight), aColor);
}

bool HitBox::CheckCollision(HitBox aHitbox)
{
	if (myCenterPosition.x<aHitbox.GetPos().x+(aHitbox.GetWidth()) &&
		myCenterPosition.x + myWidth > aHitbox.GetPos().x &&
		myCenterPosition.y < aHitbox.GetPos().y + (aHitbox.GetHeight()) &&
		myCenterPosition.y + (myHeight) > aHitbox.GetPos().y)
	{
       		return true;
	}
	return false;
}

bool HitBox::CheckifPointIsInside(Tga2D::Vector2f aPoint)
{
	if (aPoint.x > myCenterPosition.x  && aPoint.x < myCenterPosition.x+myWidth && aPoint.y > myCenterPosition.y && aPoint.y < myCenterPosition.y+myHeight)
	{
		return true;
	}

	return false;
}