#pragma once
#include "singletonBase.h"

enum STAGE
{
	START = 0,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5
};

struct tagBackGroundImg
{
	RECT rc;
	image* img;
	float x, y;
	int width, height;
};

struct tagCamera
{
	RECT rcCamera;
	float x, y;
	bool isRight;
	bool isLeft;
	bool isTop;
	bool isBottom;
};

struct tagPlayer
{
	float x, y;
	float jumpSpeed;
	float Speed;
	float gravity;
	RECT rc;
};

class allData : public singletonBase <allData>
{
private:
	tagBackGroundImg sBackGround;
	tagBackGroundImg sPixelGround;

	tagCamera sPlayerCamera;

	tagPlayer sPlayer;

	//bool isTouch;

	STAGE stage;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//배경겟
	tagBackGroundImg getBackGround() { return sBackGround; }
	tagBackGroundImg getPixelGround() { return sPixelGround; }
	RECT getPixelGroundRc() { return sPixelGround.rc; }
	RECT getPlayerRc() { return sPlayer.rc; }

	//카메라겟
	tagCamera getPlayerCamera() { return sPlayerCamera; }
	STAGE getStage() { return stage; }
	
	//플레이어겟
	tagPlayer getPlayer() { return sPlayer; }
	//bool getIsTouch() { return isTouch; }

	//배경셋
	void setBackGroundImg(image* Img) { sBackGround.img = Img; }
	void setPixelGroundImg(image* Img) { sPixelGround.img = Img; }
	void setPixelGroundX(float x) { sPixelGround.x = x; }
	void setPixelGroundY(float y) { sPixelGround.y = y; }
	void setBackGroundX(float x) { sBackGround.x = x; }
	void setBackGroundY(float y) { sBackGround.y = y; }
	void setBackGroundRc(RECT rc) { sBackGround.rc = rc; }
	void setPixelGroundRc(RECT rc) { sPixelGround.rc = rc; }

	//카메라셋
	void setPlayerCameraRc(RECT rc) { sPlayerCamera.rcCamera = rc; }
	void setPlayerCameraX(float x) { sPlayerCamera.x = x; }
	void setPlayerCameraY(float y) { sPlayerCamera.y = y; }
	void setPlayerCameraLeft(int left) { sPlayerCamera.rcCamera.left = left; }
	void setPlayerCameraRight(int right) { sPlayerCamera.rcCamera.right = right; }
	void setPlayerCameraTop(int top) { sPlayerCamera.rcCamera.top = top; }
	void setPlayerCameraBottom(int bottom) { sPlayerCamera.rcCamera.bottom = bottom; }
	void setPlayerCameraIsRight(bool right) { sPlayerCamera.isRight = right; }
	void setPlayerCameraIsLeft(bool left) { sPlayerCamera.isLeft = left; }
	void setPlayerCameraIsTop(bool top) { sPlayerCamera.isTop = top; }
	void setPlayerCameraIsBottom(bool bottom) { sPlayerCamera.isBottom = bottom; }
	void setStage(STAGE Stage) { stage = Stage; }
	
	//플레이어셋
	void setPlayerRc(RECT rc) { sPlayer.rc = rc; }
	//void setIsTouch(bool touch) { isTouch = touch; }
};

