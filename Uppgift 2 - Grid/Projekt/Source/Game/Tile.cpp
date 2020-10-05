#include "stdafx.h"
#include "Tile.h"
#include "InputHandler/InputHandler.h"
#include "Vector/Vector2.h"
#include <array>
#include <iostream>

void Tile::Init(Tga2D::Vector2f aPosition,const int aIndex)
{
	myIndex = aIndex;
	myPosition = aPosition;
	myPassable = true;
	myHitbox.Init({40,40},aPosition);
}

void Tile::ChangeColor(Tga2D::CColor aColor)
{
	myHitbox.myColor = aColor;
}

int Tile::GetIndex()
{
	return myIndex;
}

void Tile::AddObject(Object* aObject)
{
	myContainedObjects.Add(aObject);
}

CommonUtilities::GrowingArray<Object*>& Tile::GetObjects()
{
	return myContainedObjects;
}

bool Tile::CheckIfTileIsInsideLeftclick(int &aIndex,const Tga2D::CColor& aColor)
{
	std::array<float, 2> mouseCord = CommonUtilities::InputHandler::Instance().CheckMousePosInWindow(*Tga2D::CEngine::GetInstance()->GetHWND());
	Tga2D::Vector2<float> mousePos = Tga2D::Vector2<float>(mouseCord[0] / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x), mouseCord[1] / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y));
	if (myHitbox.CheckifPointIsInside(mousePos))
	{
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
		myHitbox.DrawHitbox();
		myPassable = !myPassable;
		std::cout << myIndex << std::endl;
	}

	
}

void Tile::Render()
{
	myHitbox.DrawHitbox();
}
