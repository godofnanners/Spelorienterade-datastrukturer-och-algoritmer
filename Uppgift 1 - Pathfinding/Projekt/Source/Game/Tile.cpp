#include "stdafx.h"
#include "Tile.h"
#include "InputHandler/InputHandler.h"
#include "Vector/Vector2.h"
#include <array>
#include <iostream>

void Tile::Init(Tga2D::Vector2f aPosition, const std::string& aPath,const int aIndex)
{
	myIndex = aIndex;
	mySprite = Tga2D::CSprite(aPath.c_str());
	mySprite.SetSizeRelativeToScreen({0.05f,0.05f});
	myPosition.x = aPosition.x*mySprite.GetSize().x/1.75f;
	myPosition.y = aPosition.y * mySprite.GetSize().y;
	mySprite.SetPosition(myPosition);
	myPassable = true;
	myHitbox.Init(&mySprite);
	myColor = Tga2D::CColor(1, 1, 1, 1);
}

void Tile::ChangeColor(Tga2D::CColor aColor)
{
	myColor=aColor;
}

int Tile::GetIndex()
{
	return myIndex;
}

bool Tile::CheckIfTileIsInsideLeftclick(int &aIndex,const Tga2D::CColor& aColor)
{
	std::array<float, 2> mouseCord = CommonUtilities::InputHandler::Instance().CheckMousePosInWindow(*Tga2D::CEngine::GetInstance()->GetHWND());
	Tga2D::Vector2<float> mousePos = Tga2D::Vector2<float>(mouseCord[0] / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x), mouseCord[1] / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y));
	if (myHitbox.CheckifPointIsInside(mousePos))
	{
		myHitbox.DrawHitbox(Tga2D::CColor(1, 0.5f, 1, 1));
		myColor = aColor;
		aIndex = myIndex;
		return true;
	}
	else
	{
		return false;
	}
}

void Tile::CheckIfTileIsInsideRightclick()
{
	std::array<float, 2> mouseCord = CommonUtilities::InputHandler::Instance().CheckMousePosInWindow(*Tga2D::CEngine::GetInstance()->GetHWND());
	Tga2D::Vector2<float> mousePos = Tga2D::Vector2<float>(mouseCord[0] / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x), mouseCord[1] / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y));
	if (myHitbox.CheckifPointIsInside(mousePos))
	{
		myHitbox.DrawHitbox(Tga2D::CColor(0, 0, 1, 1));
		myPassable = !myPassable;
		std::cout << myIndex << std::endl;
	}

	if (myPassable)
	{
		myColor = Tga2D::CColor(1, 1, 1, 1);
	}
	else
	{
		myColor = Tga2D::CColor(0, 0, 0.5, 1);
	}
}

void Tile::Render()
{
	mySprite.Render();
	std::array<float, 2> mouseCord = CommonUtilities::InputHandler::Instance().CheckMousePosInWindow(*Tga2D::CEngine::GetInstance()->GetHWND());
	Tga2D::Vector2<float> mousePos = Tga2D::Vector2<float>(mouseCord[0]/ static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x), mouseCord[1]/ static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y));
	if (myHitbox.CheckifPointIsInside(mousePos))
	{
		myHitbox.DrawHitbox(Tga2D::CColor(1, 0.5f, 1, 1));
		mySprite.SetColor(Tga2D::CColor(1, 0.5f, 1, 1));
		
	}
	else
	{
		myHitbox.DrawHitbox(Tga2D::CColor(1,1,1,1));
		mySprite.SetColor(myColor);
	}
}
