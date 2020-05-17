#pragma once
#include "gameNode.h"
#include "boss.h"

class bossMap : public gameNode
{
private:
	boss* ptBoss;
private:
	RECT rcBg1;
	RECT rcBg2;
	image* BackGroundImg1;
	image* BackGroundImg2;
	image* tileImg;
	image* LeftTree;
	image* RightTree;

	int count;
	int count2;
	int index;
	int index2;
	float tileX, tileY;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	boss* getPtBoss() { return ptBoss; }
};

