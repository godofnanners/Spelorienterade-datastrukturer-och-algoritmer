#pragma once
#include <array>
#include "Tile.h"
#include "AStar.hpp"
class Grid
{
public:
	void Init();
	std::array<Tile,20*20>myTiles;
	std::vector<CommonUtilities::Tile> ConvertToDijsktraVector();
	void TileOnMousePosRightClick();
	int TileOnMousePosLeftClick(bool& aFoundTile, const Tga2D::CColor& aColor);
	void ColorPath(std::vector<int>aPath);
	void ResetColors();
	void Render();
private:
};

