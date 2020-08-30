#pragma once

namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}

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
	int myStart;
	int myEnd;
};