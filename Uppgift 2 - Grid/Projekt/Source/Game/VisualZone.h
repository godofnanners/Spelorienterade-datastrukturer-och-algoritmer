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
	const Tga2D::Vector2f& GetPos();
	const HitBox& GetHitbox();
	void Render();
	void raytrace(double x0, double y0, double x1, double y1);
private:
	Tga2D::Vector2f myPosition;
	Tga2D::CSprite* mySprite;
	HitBox myHitBox;
};

