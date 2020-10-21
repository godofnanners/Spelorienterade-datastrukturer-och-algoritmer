#pragma once
#include "Rect.h"
namespace Tga2D
{
	class CSprite;
}
class HitBox :public Rect
{
public:
	HitBox();
	void Init(Tga2D::CSprite* aSprite);
	void Init(const Tga2D::Vector2f& aDim, const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aPivot = { 0,0 });
	const Tga2D::Vector2f GetPos();
	const float GetWidth();
	const float GetHeight();
	void Update(Tga2D::Vector2f aPosition);
	void DrawHitbox() const;
	bool CheckCollision(HitBox aHitbox) const;
	bool CheckifPointIsInside(Tga2D::Vector2f aPoint) const;
	Tga2D::CColor myColor;
private:
	
};

