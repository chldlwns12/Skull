#pragma once
#include "singletonBase.h"

struct tagBackGroundImg
{
	image* img;
	float x, y;
	int width, height;
};

class allData : public singletonBase <allData>
{
private:
	tagBackGroundImg sBackGround;
	tagBackGroundImg sPixelGround;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	tagBackGroundImg getBackGround() { return sBackGround; }
	tagBackGroundImg getPixelGround() { return sPixelGround; }

	void setBackGroundImg(image* Img) { sBackGround.img = Img; }
	void setPixelGroundImg(image* Img) { sPixelGround.img = Img; }
	void setPixelGroundX(float x) { sPixelGround.x = x; }
	void setPixelGroundY(float y) { sPixelGround.y = y; }
};

