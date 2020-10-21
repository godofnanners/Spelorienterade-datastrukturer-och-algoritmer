#include "stdafx.h"
#include "Rect.h"

Rect::Rect()
{

}


Rect::~Rect()
{
}

const Tga2D::Vector2<float>& Rect::GetPos() const
{
	return myPos;
}

const Tga2D::Vector2<float>& Rect::GetDimensions() const
{
	return Tga2D::Vector2<float>(myWidth, myHeight);
}

const Tga2D::Vector2<float> Rect::GetTopLeft() const
{
	return Tga2D::Vector2<float>(myPos.x - myWidth * myPivot.x, myPos.y - myHeight * myPivot.y);
}

const Tga2D::Vector2<float> Rect::GetTopRight() const
{
	return Tga2D::Vector2<float>(myPos.x + myWidth * (1 - myPivot.x), myPos.y - myHeight * myPivot.y);
}

const Tga2D::Vector2<float> Rect::GetBottomLeft() const
{
	return Tga2D::Vector2<float>(myPos.x - myWidth * myPivot.x, myPos.y + myHeight * (1 - myPivot.y));
}

const Tga2D::Vector2<float> Rect::GetBottomRight() const
{
	return Tga2D::Vector2<float>(myPos.x + myWidth * (1 - myPivot.x), myPos.y + myHeight * (1 - myPivot.y));
}

const float Rect::GetLeft() const
{
	return myPos.x - myWidth * myPivot.x;
}

const float Rect::GetRight() const
{
	return myPos.x + myWidth * (1 - myPivot.x);
}

const float Rect::GetTop() const
{
	return myPos.y - myHeight * myPivot.y;
}

const float Rect::GetBottom() const
{
	return myPos.y + myHeight * (1 - myPivot.y);
}