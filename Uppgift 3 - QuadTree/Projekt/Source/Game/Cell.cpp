#include "stdafx.h"
#include "Cell.h"
#include "Object.h"
#include "HitBox.h"
Cell::Cell()
{
	myPos = { 0,0 };
}

Cell::~Cell()
{
	for (size_t i = 0; i < myObjects.Size(); i++)
	{
		delete myObjects[i];
		myObjects[i] = nullptr;
	}
}

void Cell::AddObject(Object* aObject)
{
	myObjects.Add(aObject);

	if (myObjects.Size() > 4 && myCells.Size() == 0)
	{
		float width = myHitbox.GetWidth() * 0.5f;
		float height = myHitbox.GetHeight() * 0.5f;
		for (int newCellsIndex = 0; newCellsIndex < 4; newCellsIndex++)
		{
			Cell* newCell = new Cell();
			switch (newCellsIndex)
			{
			case 0:
				newCell->Init(myHitbox.GetTopLeft(), { width,height });
				break;
			case 1:
				newCell->Init(myHitbox.GetTopLeft() + Tga2D::Vector2f(width, 0), { width,height });
				break;
			case 2:
				newCell->Init(myHitbox.GetTopLeft() + Tga2D::Vector2f(0, height), { width,height });
				break;
			case 3:
				newCell->Init(myHitbox.GetTopLeft() + Tga2D::Vector2f(width, height), { width,height });
				break;
			default:
				assert("CellIndex went out of scope when adding adding Objects");
				break;
			}
			for (size_t objectIndex = 0; objectIndex < myObjects.Size(); objectIndex++)
			{
				if (TryToAddToCell(myObjects[objectIndex], newCell))
				{
					myObjects.RemoveCyclicAtIndex(objectIndex);
					objectIndex--;
				}
			}
			myCells.Add(newCell);
		}
	}
	else
	{
		for (size_t objectIndex = 0; objectIndex < myObjects.Size(); objectIndex++)
		{
			for (size_t cellIndex = 0; cellIndex < myCells.Size(); cellIndex++)
			{
				if (TryToAddToCell(myObjects[objectIndex], myCells[cellIndex]))
				{
					myObjects.RemoveCyclicAtIndex(objectIndex);
					
					if (myObjects.Size()>0)
					{
						objectIndex--;
					}
					break;
				}
			}
		}
	}

}

bool Cell::TryToAddToCell(Object* aObject, Cell* aCell)
{
	if (CheckIfAllAABBPointsIsInOneCell(aObject->GetHitbox(), aCell->myHitbox))
	{
		aCell->AddObject(aObject);
		return true;
	}
	else
	{
		return false;
	}
}

void Cell::OnMouseHover(Tga2D::Vector2f aMousePos)
{
	if (myHitbox.CheckifPointIsInside(aMousePos))
	{
		for (size_t i = 0; i < myObjects.Size(); i++)
		{
			myObjects[i]->SetColor({ 0,1,0,1 });
			myObjects[i]->GetHitbox().myColor = Tga2D::CColor(0, 1, 0, 1);
		}
		for (size_t i = 0; i < myCells.Size(); i++)
		{
			myCells[i]->OnMouseHover(aMousePos);
		}
	}
}

bool Cell::CheckIfAllAABBPointsIsInOneCell(const HitBox& aObjectHitbox, const HitBox& aCellHitbox)
{
	if (aCellHitbox.CheckifPointIsInside(aObjectHitbox.GetBottomLeft()) &&
		aCellHitbox.CheckifPointIsInside(aObjectHitbox.GetBottomRight()) &&
		aCellHitbox.CheckifPointIsInside(aObjectHitbox.GetTopLeft()) &&
		aCellHitbox.CheckifPointIsInside(aObjectHitbox.GetTopRight()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Cell::Init(Tga2D::Vector2f aPos, Tga2D::Vector2f aDim)
{
	myPos = aPos;
	myHitbox.Init(aDim, aPos);
}

void Cell::Render()
{
	myHitbox.DrawHitbox();
	for (size_t i = 0; i < myCells.Size(); i++)
	{
		myCells[i]->Render();
	}
}
