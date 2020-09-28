#pragma once
#include "Rect.h"
namespace Tga2D
{
	class CSprite;
}
class HitBox:Rect
{
public:
	HitBox();
	void Init(Tga2D::CSprite* aSprite);
	void Init(const Tga2D::Vector2f& aDim, const Tga2D::Vector2f& aPos);
	const Tga2D::Vector2f GetPos();
	const float GetWidth();
	const float GetHeight();
	void Update(Tga2D::Vector2f aPosition);
	void DrawHitbox(Tga2D::CColor aColor) const;
	bool CheckCollision(HitBox aHitbox) const;
	bool CheckifPointIsInside(Tga2D::Vector2f aPoint) const;
private:
	Tga2D::Vector2f myPivot;	
};

