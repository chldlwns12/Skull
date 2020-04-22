#pragma once
#include "gameNode.h"
class menuScene : public gameNode
{
private:
	image* menuBgImg;
	image* menuBaseImg;
	image* menuStartImg;
	image* menuMaptoolImg;
	image* menuExitImg;

	RECT rcStart;
	RECT rcMaptool;
	RECT rcExit;

	bool isStart;
	bool isMaptool;
	bool isExit;
	
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

