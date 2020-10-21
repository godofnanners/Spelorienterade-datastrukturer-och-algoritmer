#pragma once
#include "GrowingArray/GrowingArray.h"
namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
	template <class Type>
	class Vector2;
	typedef Vector2<float> Vector2f;
}

class Cell;
class Object;
class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);

	void Render();
private:
	Cell* myCell;
	CommonUtilities::GrowingArray<Object*>myObjects;
};