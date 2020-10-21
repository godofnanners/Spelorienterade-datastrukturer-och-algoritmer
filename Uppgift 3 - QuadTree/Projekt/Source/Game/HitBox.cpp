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
	myColor = { 1,1,1,1 };
}

void HitBox::Init(const Tga2D::Vector2f& aDim, const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aPivot)
{
	myWidth = aDim.x;
	myHeight = aDim.y;
	myPos.x = aPos.x;
	myPos.y = aPos.y;
	myPivot = aPivot;
	myColor = { 1,1,1,1 };
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

void HitBox::DrawHitbox() const
{
	Tga2D::Vector2f pos = { myPos.x / Tga2D::CEngine::GetInstance()->GetWindowSize().x, myPos.y / Tga2D::CEngine::GetInstance()->GetWindowSize().y };
	float width = myWidth / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
	float height = myHeight / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ this->GetTopLeft().x / Tga2D::CEngine::GetInstance()->GetWindowSize().x, this->GetTopLeft().y / Tga2D::CEngine::GetInstance()->GetWindowSize().y }, { this->GetTopRight().x / Tga2D::CEngine::GetInstance()->GetWindowSize().x,this->GetTopRight().y / Tga2D::CEngine::GetInstance()->GetWindowSize().y }, myColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ this->GetTopRight().x / Tga2D::CEngine::GetInstance()->GetWindowSize().x, this->GetTopRight().y / Tga2D::CEngine::GetInstance()->GetWindowSize().y }, { this->GetBottomRight().x / Tga2D::CEngine::GetInstance()->GetWindowSize().x,this->GetBottomRight().y / Tga2D::CEngine::GetInstance()->GetWindowSize().y }, myColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ this->GetBottomRight().x / Tga2D::CEngine::GetInstance()->GetWindowSize().x,this->GetBottomRight().y / Tga2D::CEngine::GetInstance()->GetWindowSize().y }, { this->GetBottomLeft().x / Tga2D::CEngine::GetInstance()->GetWindowSize().x,this->GetBottomLeft().y / Tga2D::CEngine::GetInstance()->GetWindowSize().y }, myColor);
	Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine({ this->GetBottomLeft().x / Tga2D::CEngine::GetInstance()->GetWindowSize().x,this->GetBottomLeft().y / Tga2D::CEngine::GetInstance()->GetWindowSize().y }, { this->GetTopLeft().x / Tga2D::CEngine::GetInstance()->GetWindowSize().x,this->GetTopLeft().y / Tga2D::CEngine::GetInstance()->GetWindowSize().y }, myColor);
}

bool HitBox::CheckCollision(HitBox aHitbox) const
{
	if (this->GetLeft() < aHitbox.GetRight() &&
		this->GetRight() > aHitbox.GetLeft() &&
		this->GetTop() < aHitbox.GetBottom() &&
		this->GetBottom() > aHitbox.GetTop())
	{
		return true;
	}
	return false;
}

bool HitBox::CheckifPointIsInside(Tga2D::Vector2f aPoint) const
{
	if (aPoint.x > GetLeft() && aPoint.x < GetRight() && aPoint.y > GetTop() && aPoint.y < GetBottom())
	{
		return true;
	}

	return false;
}