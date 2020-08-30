#include "stdafx.h"
#include "Grid.h"
#include <iostream>

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
		myTiles[i].Init(Tga2D::Vector2f(posX, posY), "sprites/tga_logo.dds", i);
		posX++;
	}
}



int Grid::TileOnMousePosLeftClick(bool& aFoundTile, const Tga2D::CColor& aColor)
{
	int index;
	index = -1;

	for (size_t i = 0; i < myTiles.size(); i++)
	{
		aFoundTile = myTiles[i].CheckIfTileIsInsideLeftclick(index,aColor);
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
	if (aPath.size()>0)
	{
		for (int i = 1; i < aPath.size()-1; i++)
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

void Grid::Render()
{
	for (int i = 0; i < myTiles.size(); i++)
	{
		myTiles[i].Render();
	}
}
