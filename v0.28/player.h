#pragma once
#include "gameNode.h"

enum PLAYERSTATE
{
	PLAYER_IDLE = 0,
	PLAYER_RUN,
	PLAYER_JUMP,
	PLAYER_DOUBLEJUMP,
	PLAYER_ATT,
	PLAYER_DASH
};

class player : public gameNode
{
private:
	PLAYERSTATE _playerState;

	float playerX, playerY;
	float jumpSpeed;
	float playerSpeed;
	float gravity;
	bool isJump;
	int jumpCount;
	int attCount;
	int attIndex;
	RECT rcPlayer;

	POINT ptRight;
	POINT ptLeft;
	POINT ptTop;
	POINT ptBottom;

	RECT rcRight;
	RECT rcLeft;
	RECT rcTop;
	RECT rcBottom;
	
	//플레이어 카메라
	RECT rcPlayerCamera;

	bool isLeft;
	int animationCount;
	int animationIndex;

	image* playerRunImg;
	image* playerIdleImg;
	image* playerJumpImg;
	image* playerDashImg;
	image* playerAttImg;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void PlayerAnimation();

	bool getIsJump() { return isJump; }
	RECT getRcPlayer() { return rcPlayer; }
	RECT getRcPlayerCamera() { return rcPlayerCamera; }
	RECT getRcRight() { return rcRight; }
	RECT getRcLeft() { return rcLeft; }
	RECT getRcBottom() { return rcBottom; }
	RECT getRcTop() { return rcTop; }
	
	void setPlayerY(float Y) { playerY = Y; }
	void setPlayerX(float X) { playerX = X; }
	void setJumpSpeed(float speed) { jumpSpeed = speed; }
	void setPlayerSpeed(float speed) { playerSpeed = speed; }
	void setGravity(float gv) { gravity = gv; }
	void setIsJump(bool jump) { isJump = jump; }
	void setState(PLAYERSTATE state) { _playerState = state; }
	void setCameraRight(int right) { rcPlayerCamera.right = right; }
	void setCameraLeft(int left) { rcPlayerCamera.left = left; }
};

