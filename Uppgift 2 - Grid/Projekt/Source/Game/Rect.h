#pragma once
#include"Vector/Vector2.h"
class Rect
{
public:
	Rect();
	virtual ~Rect();
	const virtual Tga2D::Vector2<float>& GetPos() const;
	const virtual Tga2D::Vector2<float>& GetDimensions() const;
	
	const virtual Tga2D::Vector2<float> GetTopLeft() const;
	const virtual Tga2D::Vector2<float> GetTopRight() const;
	const virtual Tga2D::Vector2<float> GetBottomLeft() const;
	const virtual Tga2D::Vector2<float> GetBottomRight() const;
	const virtual float GetLeft() const;
	const virtual float GetRight() const;
	const virtual float GetTop() const;
	const virtual float GetBottom() const;
protected:
	float myWidth;
	float myHeight;
	Tga2D::Vector2<float>myPos;
};

