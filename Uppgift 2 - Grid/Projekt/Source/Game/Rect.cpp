#include "stdafx.h"
#include "Rect.h"

Rect::~Rect()
{
}

const CommonUtilities::Vector2<float>& Rect::GetPos() const
{
	return myPos;
}

const CommonUtilities::Vector2<float>& Rect::GetDimensions() const
{
	return CommonUtilities::Vector2<float>(myWidth,myHeight);
}

const CommonUtilities::Vector2<float>& Rect::GetTopLeft() const
{
	return CommonUtilities::Vector2<float>(myPos.y - myHeight * 0.5f, myPos.x - myWidth * 0.5f);
}

const CommonUtilities::Vector2<float>& Rect::GetTopRight() const
{
	return CommonUtilities::Vector2<float>(myPos.y - myHeight * 0.5f, myPos.x + myWidth * 0.5f);
}

const CommonUtilities::Vector2<float>& Rect::GetBottomLeft() const
{
	return CommonUtilities::Vector2<float>(myPos.y + myHeight * 0.5f, myPos.x - myWidth * 0.5f);
}

const CommonUtilities::Vector2<float>& Rect::GetBottomRight() const
{
	return CommonUtilities::Vector2<float>(myPos.y + myHeight * 0.5f, myPos.x + myWidth * 0.5f);
}

const float Rect::GetLeft() const
{
	return myPos.x - myWidth * 0.5f;
}

const float Rect::GetRight() const
{
	return myPos.x + myWidth * 0.5f;
}

const float Rect::GetTop() const
{
	return myPos.y - myHeight * 0.5f;
}

const float Rect::GetBottom() const
{
	return myPos.y + myHeight * 0.5f;
}