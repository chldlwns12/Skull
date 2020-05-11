#pragma once
#include "gameNode.h"
class map3 : public gameNode
{
private:
	image* backGroundImg1;
	image* backGroundImg2;
	image* backGroundImg3;
	image* backGroundImg4;
	image* object;
	image* DoorImg;
	image* F_buttonImg;
	image* InputImg;
	image* nomalRuin;
	image* uniqueRuin;
	image* lookImg;
	image* soldierRuin;
	image* samuraiRuin;

	RECT rcBg1;
	RECT rcBg2;
	RECT rcBg3;
	RECT rcBg4;
	RECT rcDoor;
	RECT rcRuin;

	float itemX, itemY;
	RECT rcItem;

	bool isDoor;
	bool isRuin;
	bool isNomal;
	bool isUnique;
	bool isLook;

	float tileX, tileY;
	float playerX;
	int doorCount, doorIndex;
	int ruinCount, ruinIndex;

	int random;

	float itemGravity;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void animation();
};

