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

	RECT rcDoor;
	RECT rcRuin;

	bool isDoor;
	bool isRuin;


public:
	HRESULT init();
	void release();
	void update();
	void render();
};

