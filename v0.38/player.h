#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum PLAYERSTATE
{
	PLAYER_IDLE = 0,
	PLAYER_RUN,
	PLAYER_JUMP,
	PLAYER_DOUBLEJUMP,
	PLAYER_ATT,
	PLAYER_ATT2,
	PLAYER_DASH,
	PLAYER_START,
	PLAYER_JUMPATT,
	PLAYER_CHANGE
};

class player : public gameNode
{
private:
	PLAYERSTATE _playerState;

	progressBar* skillCool_1;
	progressBar* skillCool_2;
	progressBar* changeCool;

	//플레이어 기본사항 - 공격력 체력 등등 추가해야함
	float playerX, playerY;
	float playerSpeed;
	int attCount;
	int attIndex;
	RECT rcPlayer;
	int playerCurrentHp;
	int playerMexHp;
	//점프
	float jumpSpeed;
	float gravity;
	bool isJump;
	bool isSky;
	int jumpCount;
	//공격
	bool isEndAtt1;
	bool isAtt1;
	bool isAtt2;
	bool isAttCool;
	int Att1CoolDown;
	int Att2CoolDown;
	//대쉬
	int Efect1;
	int Efect2;
	int Efect3;
	int Efect4;
	int Efect5;
	bool isDash;
	//스킬
	int skillCooldown_1;
	int skillCooldown_2;
	int changeCooldown;
	int headAngle;
	RECT rcHead;
	int saveX;
	bool skill1;
	bool skill2;
	bool change;

	int dashCount;
	int dashCooldown;

	//충돌
	float ptRight;
	float ptLeft;
	float ptTop;
	float ptBottom;
	RECT rcRight;
	RECT rcLeft;
	RECT rcTop;
	RECT rcBottom;
	bool isColl;
	bool isTouch;

	bool isRightPixel;
	bool isLeftPixel;
	
	//플레이어 카메라
	//RECT rcPlayerCamera;

	bool isLeft;
	int animationCount;
	int animationIndex;

	image* playerStartImg;
	image* playerRunImg;
	image* playerIdleImg;
	image* playerJumpImg;
	image* playerDashImg;
	image* playerDashEfectImg1;
	image* playerAttImg1;
	image* playerAttImg2;
	image* playerJumpAttImg;
	image* playerchangeImg;
	image* playerSkillImg;
	image* playerSkill_RImg;
	image* playerSkill_LImg;

	image* castleWall1;

	bool isMove;

	RECT rcFront;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void PlayerAnimation();
	void PixelCollision();
	void playerMove();
	void playerCooldown();
	void setPlayer();

	bool getIsJump() { return isJump; }
	bool getIsLeft() { return isLeft; }
	bool getIsDash() { return isDash; }
	RECT getRcPlayer() { return rcPlayer; }
	RECT getRcRight() { return rcRight; }
	RECT getRcLeft() { return rcLeft; }
	RECT getRcBottom() { return rcBottom; }
	RECT getRcTop() { return rcTop; }
	int getPlayerMexHp() { return playerMexHp; }
	int getPlayerCurrentHp() { return playerCurrentHp; }
	
	void setPlayerY(float Y) { playerY = Y; }
	void setPlayerX(float X) { playerX = X; }
	void setJumpSpeed(float speed) { jumpSpeed = speed; }
	void setPlayerSpeed(float speed) { playerSpeed = speed; }
	void setGravity(float gv) { gravity = gv; }
	void setIsJump(bool jump) { isJump = jump; }
	void setState(PLAYERSTATE state) { _playerState = state; }
	void setJumpCount(int count) { jumpCount = count; }
	void setIsColl(bool coll) { isColl = coll; }
};

