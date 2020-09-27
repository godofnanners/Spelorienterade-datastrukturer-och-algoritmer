#pragma once
#include "VectorOnStack/VectorOnStack.h"
namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}
class Object;
class Grid;
class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aTimeDelta);
	void ResetStartnEnd();

	void Render();
private:
	Tga2D::CSprite* myTga2dLogoSprite;
	Grid* myGrid;
	CommonUtilities::VectorOnStack<Object*,20>myObjects;
	int myStart;
	int myEnd;
};