#pragma once
#include "Vector/Vector2.h"
#include "HitBox.h"
class Object
{
public:
	void Init(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aDim);
	void SetAlpha(float aAlpha);
	void Render();
private:
	Tga2D::Vector2f myPosition;
	Tga2D::CSprite* mySprite;
	HitBox myHitBox;
};

