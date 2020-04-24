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
	float gravity;
	bool isJump;
	int jumpCount;
	int attCount;
	int attIndex;
	RECT rcPlayer;
	

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
	
	void setPlayerY(float Y) { playerY = Y; }
	void setJumpSpeed(float speed) { jumpSpeed = speed; }
	void setGravity(float gv) { gravity = gv; }
	void setIsJump(bool jump) { isJump = jump; }
	void setState(PLAYERSTATE state) { _playerState = state; }
};

