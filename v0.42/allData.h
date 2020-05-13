#pragma once
#include "singletonBase.h"

enum STAGE
{
	START = 0,
	STAGE_1,
	STAGE_1_2,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5
};

enum RUINSTATE
{
	SKUL = 0,
	SOLDIER,
	SAMURAI
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
	bool isLeft;
	bool isDash;
};


class allData : public singletonBase <allData>
{
private:
	tagBackGroundImg sBackGround;
	tagBackGroundImg sPixelGround;
	tagBackGroundImg sDoor;

	tagCamera sPlayerCamera;
	tagCamera sPixelCamera;

	tagPlayer sPlayer;

	RECT rcNext;

	STAGE stage;

	RUINSTATE ruinState;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//배경겟
	tagBackGroundImg getBackGround() { return sBackGround; }
	tagBackGroundImg getPixelGround() { return sPixelGround; }
	tagBackGroundImg getDoor() { return sDoor; }
	RECT getPixelGroundRc() { return sPixelGround.rc; }
	RECT getNextRc() { return rcNext; }

	//카메라겟
	tagCamera getPlayerCamera() { return sPlayerCamera; }
	tagCamera getPixelCamera() { return sPixelCamera; }

	STAGE getStage() { return stage; }
	
	//플레이어겟
	tagPlayer getPlayer() { return sPlayer; }
	RECT getPlayerRc() { return sPlayer.rc; }
	RUINSTATE getPlayerRuin() { return ruinState; }
	//bool getIsTouch() { return isTouch; }

	//배경셋
	void setBackGroundImg(image* Img) { sBackGround.img = Img; }
	void setPixelGroundImg(image* Img) { sPixelGround.img = Img; }
	void setDoorImg(image* Img) { sDoor.img = Img; }

	void setPixelGroundX(float x) { sPixelGround.x = x; }
	void setPixelGroundY(float y) { sPixelGround.y = y; }
	void setBackGroundX(float x) { sBackGround.x = x; }
	void setBackGroundY(float y) { sBackGround.y = y; }
	void setDoorX(float x) { sDoor.x = x; }
	void setDoorY(float y) { sDoor.y = y; }

	void setBackGroundRc(RECT rc) { sBackGround.rc = rc; }
	void setPixelGroundRc(RECT rc) { sPixelGround.rc = rc; }
	void setDoorRc(RECT rc) { sDoor.rc = rc; }

	void setNextRc(RECT rc) { rcNext = rc; }

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

	void setPixelCameraRc(RECT rc) { sPixelCamera.rcCamera = rc; }
	void setPixelCameraX(float x) { sPixelCamera.x = x; }
	void setPixelCameraY(float y) { sPixelCamera.y = y; }
	void setPixelCameraLeft(int left) { sPixelCamera.rcCamera.left = left; }
	void setPixelCameraRight(int right) { sPixelCamera.rcCamera.right = right; }
	void setPixelCameraTop(int top) { sPixelCamera.rcCamera.top = top; }
	void setPixelCameraBottom(int bottom) { sPixelCamera.rcCamera.bottom = bottom; }
	void setPixelCameraIsRight(bool right) { sPixelCamera.isRight = right; }
	void setPixelCameraIsLeft(bool left) { sPixelCamera.isLeft = left; }
	void setPixelCameraIsTop(bool top) { sPixelCamera.isTop = top; }
	void setPixelCameraIsBottom(bool bottom) { sPixelCamera.isBottom = bottom; }
	
	//플레이어셋
	void setPlayerRc(RECT rc) { sPlayer.rc = rc; }
	void setPlayerX(float x) { sPlayer.x = x; }
	void setPlayerY(float y) { sPlayer.y = y; }
	void setPlayerLeft(int left) { sPlayer.rc.left = left; }
	void setPlayerRight(int right) { sPlayer.rc.right = right; }
	void setPlayerRuin(RUINSTATE state) { ruinState = state; }
	void setPlayerIsLeft(bool left) { sPlayer.isLeft = left; }
	void setPlayerIsDash(bool dash) { sPlayer.isLeft = dash; }

	//void setIsTouch(bool touch) { isTouch = touch; }
};

