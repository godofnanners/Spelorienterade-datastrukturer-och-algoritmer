#pragma once
#include <array>
#include "Tile.h"

class Grid
{
public:
	void Init();
	std::array<Tile,20*20>myTiles;
	void TileOnMousePosRightClick();
	int TileOnMousePosLeftClick(bool& aFoundTile, const Tga2D::CColor& aColor);
	void ColorPath(std::vector<int>aPath);
	void ResetColors();
	void FindAnInsertObjectInTile(Object* aObject, Tga2D::Vector2f myPos);
	CommonUtilities::GrowingArray<Object*> GetObjectsInAABB(const Rect& aHitbox);
	bool CheckColisionAABB(const Rect& aRect1, const Rect& aRect2);
	bool CheckIfPointIsInsideRect(const CommonUtilities::Vector2<float>& aPoint, const Rect& aRect);
	void Render();
private:
	CommonUtilities::GrowingArray<Tile*>myTilesinVision;
};

