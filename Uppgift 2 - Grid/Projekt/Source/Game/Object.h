#pragma once
#include "Vector/Vector2.h"
#include "HitBox.h"
class Object
{
public:
	void Init(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aDim);
	void SetAlpha(float aAlpha);
	void SetColor(Tga2D::CColor aColor);
	void SetPos(const Tga2D::Vector2f& aPosition);
	void Render();
	Tga2D::Vector2f GetPos();
	const HitBox& GetHitbox();
private:
	Tga2D::CColor myColor;
	Tga2D::Vector2f myPosition;
	Tga2D::CSprite* mySprite;
	HitBox myHitBox;
};

