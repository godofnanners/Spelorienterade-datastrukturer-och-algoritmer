#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include "InputHandler/InputHandler.h"
#include "Random/Random.hpp"
#include "InputHandler/InputKeys.h"
#include <iostream>
#include "Object.h"
#include "tga2d/math/vector2.h"
#include "Vector/Vector2.h"
#include "Cell.h"

CGameWorld::CGameWorld()
{
	myCell = nullptr;
}

CGameWorld::~CGameWorld()
{
	
}

void CGameWorld::Init()
{
	myCell = new Cell();
	myCell->Init({ 1,1 }, { 700,700 });
}


void CGameWorld::Update(float /*aTimeDelta*/)
{

	for (size_t i = 0; i < myObjects.Size(); i++)
	{
		myObjects[i]->SetColor({ 1,1,1,1 });
		myObjects[i]->GetHitbox().myColor = Tga2D::CColor( 1,1,1,1 );
	}

	std::array<float, 2> mouseCord = CommonUtilities::InputHandler::Instance().CheckMousePosInWindow(*Tga2D::CEngine::GetInstance()->GetHWND());
	Tga2D::Vector2<float> mousePos = Tga2D::Vector2<float>(mouseCord[0], mouseCord[1]);
	
	if (CommonUtilities::InputHandler::Instance().CheckIfMouseButtonIsPressed(static_cast<int>(InputKeys::eMouseButtons::eLBUTTON)))
	{
		Object* newObject = new Object();
		newObject->Init(mousePos, { 10,10 });
		myObjects.Add(newObject);
		myCell->AddObject(newObject);
	}

	myCell->OnMouseHover(mousePos);

}

void CGameWorld::Render()
{
	myCell->Render();
	for (size_t i = 0; i < myObjects.Size(); i++)
	{
		myObjects[i]->Render();
	}
}