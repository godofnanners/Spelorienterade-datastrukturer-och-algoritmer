#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputHandler/InputHandler.h"
#include "Grid.h"
#include "Random/Random.hpp"
#include "InputHandler/InputKeys.h"
#include <iostream>
#include "Object.h"
#include "VisualZone.h"
#include "tga2d/math/vector2.h"
#include "Vector/Vector2.h"
CGameWorld::CGameWorld()
{
	myTga2dLogoSprite = nullptr;
	myGrid = nullptr;
	myVisualZone = nullptr;
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
	float gridSize = 40 * 20;
	CommonUtilities::GrowingArray<Object*> createdObjects;
	for (size_t i = 0; i < 15; i++)
	{
		Tga2D::Vector2f position = Tga2D::Vector2f(CommonUtilities::GetRandomFloat(0+20, gridSize-20), CommonUtilities::GetRandomFloat(0+20, gridSize-20));
		Object* object = new Object();
		object->Init(position, Tga2D::Vector2f(40, 40));
		object->SetAlpha(0.5f);
		myObjects.Add(object);
		myGrid->FindAnInsertObjectInTile(object, position);
		
		for (size_t j = 0; j < createdObjects.Size(); j++)
		{
			if (createdObjects[j]->GetHitbox().CheckCollision(object->GetHitbox()))
			{
				Tga2D::Vector2f newPosition = Tga2D::Vector2f(CommonUtilities::GetRandomFloat(0 + 20, gridSize - 20), CommonUtilities::GetRandomFloat(0 + 20, gridSize - 20));
				object->SetPos(newPosition);
				j--;
			}
		}
		createdObjects.Add(object);
	}
	

	CommonUtilities::InputHandler::Instance().CheckMousePos();

}


void CGameWorld::Reset()
{
	delete myVisualZone;
	myVisualZone = nullptr;
	for (size_t i = 0; i < myObjects.Size(); i++)
	{
		Object* object = myObjects[i];
		object->SetColor({ 1,1,1,0.5f });
	}
	for (size_t i = 0; i < myGrid->myTiles.size(); i++)
	{
		myGrid->myTiles[i].ChangeColor({ 1,1,1,1 });
	}
}

void CGameWorld::SetMyVisualZone(const Tga2D::Vector2f& aPos)
{
	if (myVisualZone!= nullptr)
	{
		Reset();
	}

	myVisualZone = new VisualZone();
	myVisualZone->Init(aPos, { 40,40 });
	CommonUtilities::GrowingArray<Object*> myInZoneObjects = myGrid->GetObjectsInAABB(myVisualZone->GetHitbox());

	for (size_t i = 0; i < myInZoneObjects.Size(); i++)
	{
		Tga2D::Vector2f centerPos = myVisualZone->GetPos();
		Tga2D::Vector2f objectPos = myInZoneObjects[i]->GetPos();
		if ((CommonUtilities::Vector2(centerPos.x,centerPos.y)- CommonUtilities::Vector2(objectPos.x, objectPos.y)).Length()<300)
		{
			myInZoneObjects[i]->SetAlpha(1);
			if (myGrid->raytrace(centerPos.x, centerPos.y, objectPos.x, objectPos.y, myInZoneObjects[i]))
			{
				myInZoneObjects[i]->SetColor({ 1, 0, 0, 1 });
			}
		}
		else
		{
			myInZoneObjects.RemoveCyclicAtIndex(i);
			i--;
		}

	}
}

void CGameWorld::Update(float /*aTimeDelta*/)
{
	if (CommonUtilities::InputHandler::Instance().CheckIfMouseButtonIsPressed(static_cast<int>(InputKeys::eMouseButtons::eLBUTTON)))
	{
		std::array<float, 2> mouseCord = CommonUtilities::InputHandler::Instance().CheckMousePosInWindow(*Tga2D::CEngine::GetInstance()->GetHWND());
		Tga2D::Vector2<float> mousePos = Tga2D::Vector2<float>(mouseCord[0] / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x), mouseCord[1] / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().y));

		SetMyVisualZone({ mouseCord[0],mouseCord[1] });
	}
	int nodeClicked = -1;
	bool foundTile = false;

}

void CGameWorld::ResetStartnEnd()
{
	myStart = -1;
	myEnd = -1;
}

void CGameWorld::Render()
{
	for (size_t i = 0; i < myObjects.Size(); i++)
	{
		myObjects[i]->Render();
	}
	if (myVisualZone!=nullptr)
	{
		myVisualZone->Render();
	}
	myGrid->Render();
	//myTga2dLogoSprite->Render();
}