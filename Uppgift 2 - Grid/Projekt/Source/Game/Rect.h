#pragma once
#include"Vector/Vector2.h"
class Rect
{
public:
	virtual ~Rect();
	const CommonUtilities::Vector2<float>& GetPos() const;
	const CommonUtilities::Vector2<float>& GetDimensions() const;
	
	const CommonUtilities::Vector2<float>& GetTopLeft() const;
	const CommonUtilities::Vector2<float>& GetTopRight() const;
	const CommonUtilities::Vector2<float>& GetBottomLeft() const;
	const CommonUtilities::Vector2<float>& GetBottomRight() const;
	const float GetLeft() const;
	const float GetRight() const;
	const float GetTop() const;
	const float GetBottom() const;
protected:
	float myWidth;
	float myHeight;
	CommonUtilities::Vector2<float>myPos;
};

