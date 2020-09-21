#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputHandler/InputHandler.h"
#include "Grid.h"
#include "Random/Random.hpp"
#include "InputHandler/InputKeys.h"
#include <iostream>
CGameWorld::CGameWorld()
{
	myTga2dLogoSprite = nullptr;
	myGrid = nullptr;
}

CGameWorld::~CGameWorld()
{
	delete myTga2dLogoSprite;
	myTga2dLogoSprite = nullptr;
}

void CGameWorld::Init()
{
	myGrid = new Grid();
	myGrid->Init();
	myStart = -1;
	myEnd = -1;
	/*myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.8f, 0.5f });
	myTga2dLogoSprite->SetSizeRelativeToScreen({ 0.2,0.2 });*/
	CommonUtilities::InputHandler::Instance().CheckMousePos();
}


void CGameWorld::Update(float /*aTimeDelta*/)
{
	//if (CommonUtilities::InputHandler::Instance().CheckIfMouseButtonIsPressed(static_cast<int>(InputKeys::eMouseButtons::eLBUTTON)))
	int nodeClicked = -1;
	bool foundTile = false;
	if (CommonUtilities::InputHandler::Instance().CheckIfMouseButtonIsPressed(static_cast<int>(InputKeys::eMouseButtons::eLBUTTON)) && myStart < 0 && myEnd < 0)
	{
		ResetStartnEnd();
		myGrid->ResetColors();
	}
	
	if (CommonUtilities::InputHandler::Instance().CheckIfMouseButtonIsPressed(static_cast<int>(InputKeys::eMouseButtons::eLBUTTON)) && myStart == -1)
	{
		nodeClicked = myGrid->TileOnMousePosLeftClick(foundTile,Tga2D::CColor(0,1,0,1));
		if (foundTile)
		{
			myStart = nodeClicked;
		}
	}
	else if (CommonUtilities::InputHandler::Instance().CheckIfMouseButtonIsPressed(static_cast<int>(InputKeys::eMouseButtons::eLBUTTON)) && myEnd == -1)
	{
		nodeClicked = myGrid->TileOnMousePosLeftClick(foundTile, Tga2D::CColor(1, 0, 0, 1));
		if (foundTile)
		{
			myEnd = nodeClicked;
		}
	}

	if (CommonUtilities::InputHandler::Instance().CheckIfMouseButtonIsPressed(static_cast<int>(InputKeys::eMouseButtons::eLBUTTON)) && myStart != -1 && myEnd != -1)
	{
		
		ResetStartnEnd();
	}

	if (CommonUtilities::InputHandler::Instance().CheckIfMouseButtonIsPressed(static_cast<int>(InputKeys::eMouseButtons::eRBUTTON)))
	{
		myGrid->TileOnMousePosRightClick();
	}
}

void CGameWorld::ResetStartnEnd()
{
	myStart = -1;
	myEnd = -1;
}

void CGameWorld::Render()
{
	myGrid->Render();
	//myTga2dLogoSprite->Render();
}