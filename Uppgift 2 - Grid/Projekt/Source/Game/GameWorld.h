#pragma once
#include "VectorOnStack/VectorOnStack.h"
namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
	template <class Type>
	class Vector2;
	typedef Vector2<float> Vector2f;
}
class Object;
class Grid;
class VisualZone;
class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Reset();
	void SetMyVisualZone(const Tga2D::Vector2f& aPos);
	void Update(float aTimeDelta);
	void ResetStartnEnd();

	void Render();
private:
	Tga2D::CSprite* myTga2dLogoSprite;
	Grid* myGrid;
	CommonUtilities::VectorOnStack<Object*,20>myObjects;
	VisualZone* myVisualZone;
	int myStart;
	int myEnd;
};