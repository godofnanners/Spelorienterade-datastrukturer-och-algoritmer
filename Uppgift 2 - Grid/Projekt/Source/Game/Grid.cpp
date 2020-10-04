#include "stdafx.h"
#include "Grid.h"
#include <iostream>
#include "Rect.h"
#include "Vector/Vector2.h"
#include "Rect.h"

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
		myTiles[i].Init(Tga2D::Vector2f(posX * 40, posY * 40), i);
		posX++;
	}
}


int Grid::TileOnMousePosLeftClick(bool& aFoundTile, const Tga2D::CColor& aColor)
{
	int index;
	index = -1;

	for (size_t i = 0; i < myTiles.size(); i++)
	{
		aFoundTile = myTiles[i].CheckIfTileIsInsideLeftclick(index, aColor);
		if (aFoundTile)
		{
			std::cout << index << std::endl;
			break;
		}
	}
	return index;
}

void Grid::TileOnMousePosRightClick()
{
	for (size_t i = 0; i < myTiles.size(); i++)
	{
		myTiles[i].CheckIfTileIsInsideRightclick();
	}
}

void Grid::ColorPath(std::vector<int> aPath)
{
	if (aPath.size() > 0)
	{
		for (int i = 1; i < aPath.size() - 1; i++)
		{
			myTiles[aPath[i]].ChangeColor({ 1,1,0,1 });
		}
	}
}

void Grid::ResetColors()
{
	for (size_t i = 0; i < myTiles.size(); i++)
	{
		if (myTiles[i].myPassable)
		{
			myTiles[i].ChangeColor(Tga2D::CColor(1, 1, 1, 1));
		}
	}
}

void Grid::FindAnInsertObjectInTile(Object* aObject, Tga2D::Vector2f myPos)
{
	unsigned int tileColumn = (myPos.x * 0.025f);
	unsigned int tileRow = (myPos.y * 0.025f);

	unsigned int tileIndex = tileColumn + tileRow * 20;

	myTiles[tileIndex].AddObject(aObject);
}

CommonUtilities::GrowingArray<Object*> Grid::GetObjectsInAABB(const Rect& aRect)
{

	Tga2D::Vector2f topLeft = aRect.GetTopLeft();
	Tga2D::Vector2f topRight = aRect.GetTopRight();
	Tga2D::Vector2f bottomRight = aRect.GetBottomRight();
	Tga2D::Vector2f bottomLeft = aRect.GetBottomLeft();

	topLeft *= 0.025f;
	topRight *= 0.025f;
	bottomRight *= 0.025f;
	bottomLeft *= 0.025f;

	unsigned int topLeftIndex = (topLeft.x) + (topLeft.y * 20);
	unsigned int topRightIndex = (topRight.x) + (topRight.y * 20);
	unsigned int bottomLeftIndex = (bottomLeft.x) + (bottomLeft.y * 20);
	unsigned int bottomRightIndex = (bottomRight.x) + (bottomRight.y * 20);
	unsigned int size = topRightIndex - topLeftIndex;
	CommonUtilities::GrowingArray<Object*> objectList;

	for (int column = topLeftIndex; column < topRightIndex; column++)
	{
		for (int row = bottomLeftIndex; row < bottomRightIndex; row++)
		{
			CommonUtilities::GrowingArray<Object*>ObjectsInTile = myTiles[column + (row * 20)].GetObjects();
			for (int objectIndex = 0; objectIndex < ObjectsInTile.Size(); objectIndex++)
			{
				objectList.Add(ObjectsInTile[objectIndex]);
			}
		}
	}
	return objectList;
}

bool Grid::CheckColisionAABB(const Rect& aRect1, const Rect& aRect2)
{

	const Tga2D::Vector2<float>& pos1 = aRect1.GetPos();
	const Tga2D::Vector2<float>& dim1 = aRect1.GetDimensions();

	const Tga2D::Vector2<float>& pos2 = aRect2.GetPos();
	const Tga2D::Vector2<float>& dim2 = aRect2.GetDimensions();

	return (pos1.x < pos2.x + dim2.x &&
		pos1.x + dim1.x > pos2.x &&
		pos1.y < pos2.y + dim2.y &&
		pos1.y + dim1.y > pos2.y);
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
