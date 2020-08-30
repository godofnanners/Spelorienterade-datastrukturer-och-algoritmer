#pragma once
#include "tga2d/sprite/sprite.h"

#include <string>
#include "HitBox.h"
class Tile
{
public:
	Tga2D::CSprite mySprite;
	Tga2D::Vector2f myPosition;
	HitBox myHitbox;

	bool myPassable;
	void Init(Tga2D::Vector2f aPosition,const std::string& aPath, const int aIndex);
	void ChangeColor(Tga2D::CColor aColor);
	int GetIndex();
	void CheckIfTileIsInsideRightclick();
	bool CheckIfTileIsInsideLeftclick(int& aIndex, const Tga2D::CColor& aColor);
	void Render();
private:
	Tga2D::CColor myColor;
	int myIndex;
};

