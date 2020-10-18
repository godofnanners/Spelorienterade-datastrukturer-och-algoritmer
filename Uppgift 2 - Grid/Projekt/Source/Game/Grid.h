#pragma once
#include <array>
#include "Tile.h"

class Object;
class Grid
{
public:
	void Init();
	std::array<Tile,20*20>myTiles;
	void TileOnMousePosRightClick();
	int TileOnMousePosLeftClick(bool& aFoundTile, const Tga2D::CColor& aColor);
	void ResetColors();
	void FindAnInsertObjectInTile(Object* aObject, Tga2D::Vector2f myPos);
	Tile& GetTileFromPos(const Tga2D::Vector2f& aPos);
	CommonUtilities::GrowingArray<Object*> GetObjectsInAABB(const Rect& aHitbox);
	bool CheckColisionAABB(const Rect& aRect1, const Rect& aRect2);
	bool CheckIfPointIsInsideRect(const CommonUtilities::Vector2<float>& aPoint, const Rect& aRect);
	void Render();
	bool raytrace(double x0, double y0, double x1, double y1,Object*aObject);
private:
	bool IsTileContainingNonstartingObjects(float x, float y, Object* aStartingObject);
	CommonUtilities::GrowingArray<Tile*>myTilesinVision;
};

