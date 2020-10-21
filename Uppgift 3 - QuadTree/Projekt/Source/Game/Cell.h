#pragma once
#include "HitBox.h"
#include <array>
#include "VectorOnStack/VectorOnStack.h"
#include "GrowingArray/GrowingArray.h"
class Object;
class Cell
{
public:
	Cell();
	~Cell();
	void AddObject(Object* aObject);
	bool TryToAddToCell(Object* aObject, Cell* aCell);
	void OnMouseHover(Tga2D::Vector2f aMousePos);
	bool CheckIfAllAABBPointsIsInOneCell(const HitBox& aObjectHitbox, const HitBox& aCellHitbox);
	void Init(Tga2D::Vector2f aPos,Tga2D::Vector2f aDim);

	void Render();

private:
	Tga2D::Vector2f myPos;
	HitBox myHitbox;
	CommonUtilities::GrowingArray<Object*>myObjects;
	CommonUtilities::VectorOnStack<Cell*, 4>myCells;
};

