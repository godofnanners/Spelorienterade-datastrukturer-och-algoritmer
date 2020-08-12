#pragma once

namespace Tga2D
{
	class CSprite;
}
class HitBox
{
public:
	HitBox();
	void Init(Tga2D::CSprite* aSprite);
	const Tga2D::Vector2f GetPos();
	const float GetWidth();
	const float GetHeight();
	void Update(Tga2D::Vector2f aPosition);
	void DrawHitbox(Tga2D::CColor aColor);
	bool CheckCollision(HitBox aHitbox);
	bool CheckifPointIsInside(Tga2D::Vector2f aPoint);
private:
	Tga2D::Vector2f myCenterPosition;
	Tga2D::Vector2f myPivot;
	float myWidth;
	float myHeight;
	
};

