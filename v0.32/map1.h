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
	image* objectImg;

	RECT rcBackGround1;
	RECT rcBackGround2;
	RECT rcBackGround3;
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

