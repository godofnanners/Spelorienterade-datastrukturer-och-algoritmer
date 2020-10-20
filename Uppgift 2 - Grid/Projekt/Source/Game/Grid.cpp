#include "stdafx.h"
#include "Grid.h"
#include <iostream>
#include "Rect.h"
#include "Vector/Vector2.h"
#include "Rect.h"
#include "Object.h"

void Grid::Init()
{
	float posY = 0;
	float posX = 0;
	for (int i = 0; i < myTiles.size(); i++)
	{
		posY = static_cast<int>(i / 20);
		if (posX > 19)
		{
			posX = 0;
		}
		myTiles[i].Init(Tga2D::Vector2f((posX * 40) + 20, (posY * 40) + 20), i);
		posX++;
	}
}

void Grid::FindAnInsertObjectInTile(Object* aObject, Tga2D::Vector2f aPos)
{
	const HitBox& hitbox = aObject->GetHitbox();

	GetTileFromPos(hitbox.GetTopLeft()).AddObject(aObject);
	GetTileFromPos(hitbox.GetTopRight()).AddObject(aObject);
	GetTileFromPos(hitbox.GetBottomLeft()).AddObject(aObject);
	GetTileFromPos(hitbox.GetBottomRight()).AddObject(aObject);
}

Tile& Grid::GetTileFromPos(const Tga2D::Vector2f& aPos)
{
	unsigned int tileColumn = (aPos.x * 0.025f);
	unsigned int tileRow = (aPos.y * 0.025f);

	unsigned int tileIndex = tileColumn + tileRow * 20;

	return myTiles[tileIndex];
}

CommonUtilities::GrowingArray<Object*> Grid::GetObjectsInAABB(const Rect& aRect)
{

	Tga2D::Vector2f topLeft = aRect.GetTopLeft();
	Tga2D::Vector2f topRight = aRect.GetTopRight();
	Tga2D::Vector2f bottomRight = aRect.GetBottomRight();
	Tga2D::Vector2f bottomLeft = aRect.GetBottomLeft();

	int topleftColumn = topLeft.x * 0.025f;
	topleftColumn= topleftColumn > 0 ? topleftColumn : 0;
	topleftColumn = topleftColumn < 20 ? topleftColumn : 20;

	int topleftRow = topLeft.y * 0.025f;
	topleftRow = topleftRow > 0 ? topleftRow : 0;
	topleftRow = topleftRow < 19 ? topleftRow : 19;

	int toprightColumn = topRight.x * 0.025f;
	toprightColumn = toprightColumn > 0 ? toprightColumn : 0;
	toprightColumn = toprightColumn < 19 ? toprightColumn : 19;
	
	int toprightRow = topRight.y * 0.025f;
	toprightRow = toprightRow > 0 ? toprightRow : 0;
	toprightRow = toprightRow < 19 ? toprightRow : 19;
	
	int bottomRightColumn = bottomRight.x * 0.025f;
	bottomRightColumn = bottomRightColumn > 0 ? bottomRightColumn : 0;
	bottomRightColumn = bottomRightColumn < 19 ? bottomRightColumn : 19;

	int bottomRightRow = bottomRight.y * 0.025f;
	bottomRightRow = bottomRightRow > 0 ? bottomRightRow : 0;
	bottomRightRow = bottomRightRow < 19 ? bottomRightRow : 19;

	int topLeftIndex = (topleftColumn)+(topleftRow * 20);
	int topRightIndex = (toprightColumn)+(toprightRow * 20);
	int bottomRightIndex = (bottomRightColumn)+(bottomRightRow * 20);
	int rowSize = topRightIndex - topLeftIndex;
	int rowIndex = topLeftIndex;
	CommonUtilities::GrowingArray<Object*> objectList;
	myTilesinVision.RemoveAll();

	for (int tileIndex = topLeftIndex; tileIndex < bottomRightIndex + 1; tileIndex++)
	{
		if (rowSize < tileIndex - rowIndex)
		{
			rowIndex += 20;
			tileIndex = rowIndex;
		}
		if (tileIndex >= 400 || tileIndex < 0)
		{
			//skip if index is outside of grid
			continue;
		}
		myTilesinVision.Add(&myTiles[tileIndex]);
		CommonUtilities::GrowingArray<Object*>ObjectsInTile = myTiles[tileIndex].GetObjects();
		for (int objectIndex = 0; objectIndex < ObjectsInTile.Size(); objectIndex++)
		{
			if (objectList.Find(ObjectsInTile[objectIndex]) == objectList.FoundNone)
			{
				objectList.Add(ObjectsInTile[objectIndex]);
			}
		}
		myTiles[tileIndex].ChangeColor({ 1, 0, 1, 1 });
	}
	return objectList;
}

bool Grid::CheckIfPointIsInsideRect(const CommonUtilities::Vector2<float>& aPoint, const Rect& aRect)
{
	return (aPoint.x > aRect.GetLeft() && aPoint.x < aRect.GetRight() && aPoint.y > aRect.GetTop() && aPoint.y < aRect.GetBottom());
}

void Grid::Render()
{
	for (int i = 0; i < myTiles.size(); i++)
	{
		myTiles[i].Render();
	}
}

bool Grid::raytrace(double x0, double y0, double x1, double y1, Object* aStartingObject)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x = x0;
	int y = y0;
	int n = 1 + dx + dy;
	int x_inc = (x1 > x0) ? 1 : -1;
	int y_inc = (y1 > y0) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;

	for (; n > 0; --n)
	{
		int amountOfObjectsInTile = GetTileFromPos({ (float)x, (float)y }).GetObjects().Size();
		CommonUtilities::GrowingArray<Object*>objects = GetTileFromPos({ (float)x, (float)y }).GetObjects();

		if (IsTileContainingNonstartingObjects(x, y, aStartingObject))
		{
			for (size_t i = 0; i < amountOfObjectsInTile; i++)
			{
				if (objects[i]->GetHitbox().CheckifPointIsInside({ (float)x, (float)y }) && aStartingObject != objects[i])
				{
					return true;
				}
			}
		}

		if (error > 0)
		{
			y += y_inc;
			error -= dx;
		}
		else
		{
			x += x_inc;
			error += dy;
		}
	}
	return false;
}

bool Grid::IsTileContainingNonstartingObjects(float x, float y, Object* aStartingObject)
{
	CommonUtilities::GrowingArray<Object*>objects = GetTileFromPos({ (float)x, (float)y }).GetObjects();
	int amountOfObjectsInTile = objects.Size();

	if (amountOfObjectsInTile > 1)
	{
		return true;
	}
	else if (amountOfObjectsInTile == 1 && objects[0] != aStartingObject)
	{
		return true;
	}

	return false;
}