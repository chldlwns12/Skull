#pragma once
#include "gameNode.h"
class map1 : public gameNode
{
private:
	//Ω√¿€∏ 
	image* bgImg;
	image* skyImg1;
	image* skyImg2;
	image* chanImg1;
	image* chanImg2;
	image* chanImg3;
	image* cloudImg1;
	image* cloudImg2;
	image* cloudImg3;
	image* cloudImg4;
	image* cloudImg5;
	image* objectImg;
	image* castle;
	image* castleWall2;
	image* castleWall3;
	image* mountain1;
	image* mountain2;

	//æ∆∑ß∏ 
	image* tileImg;
	image* objectImg2;
	image* doorImg;
	RECT rcDoor;
	int doorCount;
	int doorIndex;
	image* F_Button;

	RECT rcBackGround1;
	RECT rcBackGround2;
	RECT rcBackGround3;
	RECT rcBackGround4;
	RECT rcBackGround5;

	float tileX, tileY;
	int loopX;

	bool isChange;
	bool isMove;

	//RECT rcNext;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

