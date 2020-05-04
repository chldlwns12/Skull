#pragma once
#include "gameNode.h"
class map1 : public gameNode
{
private:
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
	//image* castleWall1;
	image* castleWall2;
	image* castleWall3;
	image* mountain1;
	image* mountain2;

	RECT rcBackGround1;
	RECT rcBackGround2;
	RECT rcBackGround3;
	RECT rcBackGround4;

	float tileX, tileY;
	int loopX;

	bool isChange;
	bool isMove;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

