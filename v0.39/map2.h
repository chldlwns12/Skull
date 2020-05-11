#pragma once
#include "gameNode.h"
class map2 : public gameNode
{
private:
	image* backGroundImg1;
	image* backGroundImg2;
	image* backGroundImg3;
	image* backGroundImg4;
	image* object;
	image* front;
	image* DoorImg;
	image* F_buttonImg;
	image* InputImg;

	RECT rcBg1;
	RECT rcBg2;
	RECT rcBg3;
	RECT rcBg4;

	//충돌박스
	RECT rcColl1;

	RECT rcDoor;
	bool isDoor;

	float tileX, tileY;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

