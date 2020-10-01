#pragma once
#include "HitBox.h"

namespace Tga2D
{
	class CSprite;
}

class VisualZone
{
public:
	VisualZone();
	void Init(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aDim);
	Tga2D::Vector2f GetPos();
	void Render();
private:
	Tga2D::Vector2f myPosition;
	Tga2D::CSprite* mySprite;
	HitBox myHitBox;
};

