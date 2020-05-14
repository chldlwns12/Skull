#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "bullet.h"

enum PLAYERSTATE
{
	PLAYER_IDLE = 0,
	PLAYER_RUN,
	PLAYER_JUMP,
	PLAYER_DOUBLEJUMP,
	PLAYER_ATT,
	PLAYER_ATT2,
	PLAYER_ATT3,
	PLAYER_DASH,
	PLAYER_START,
	PLAYER_JUMPATT,
	PLAYER_SKILL1,
	PLAYER_SKILL2,
	PLAYER_CHANGE,
	PLAYER_NAPDO
};

class player : public gameNode
{
private:
	progressBar* skillCool_1;
	progressBar* skillCool_2;
	progressBar* changeCool;
	Skul* Head;
private:
	PLAYERSTATE _playerState;


	//플레이어 기본사항 - 공격력 체력 등등 추가해야함
	float playerX, playerY;
	float playerSpeed;
	int attCount;
	int attIndex;
	RECT rcPlayer;
	int playerCurrentHp;
	int playerMexHp;
	float moveX, moveY;
	//점프
	float jumpSpeed;
	float gravity;
	bool isJump;
	bool isSky;
	int jumpCount;
	//공격
	bool isEndAtt1;
	bool isEndAtt2;
	bool isEndAtt3;
	//bool isAtt1;
	//bool isAtt2;
	//bool isAtt3;
	int Att1CoolDown;
	int Att2CoolDown;
	int Att3CoolDown;
	bool isAttCool;
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
	int CooldownMax;
	int changeCooldown;
	//int headAngle;
	RECT rcHead;
	int saveX;
	bool skill1;
	bool skill2;
	bool change;
	float headAngle;
	float headGravity;
	bool isSoldierSkill;
	bool isSamuraiSkill1;
	bool isSamuraiSkill2;
	int skillEfect1;
	int skillEfect2;
	int skillEfect3;
	int skillEfect4;
	int skillEfect5;

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

	//머리있는 이미지
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
	//머리없는 이미지
	image* nonRunImg;
	image* nonIdleImg;
	image* nonJumpImg;
	image* nonDashImg;
	image* nonDashEfectImg;
	image* nonAttImg1;
	image* nonAttImg2;
	image* nonJumpAttImg;
	//병사해골 이미지
	image* soldierRunImg;
	image* soldierIdleImg;
	image* soldierJumpImg;
	image* soldierDashImg;
	image* soldierDashEfectImg;
	image* soldierAttImg;
	image* soldierJumpAttImg;
	image* soldierChangeImg;
	image* soldierSkillImg;
	//사무라이해골 이미지
	image* samuraiRunImg;
	image* samuraiIdleImg;
	image* samuraiJumpImg;
	image* samuraiDashImg;
	image* samuraiDashEfectImg;
	image* samuraiAttImg1;
	image* samuraiAttImg2;
	image* samuraiAttImg3;
	image* samuraiJumpAttImg;
	image* samuraiChangeImg;
	image* samuraiSkillImg_1;
	image* samuraiSkillImg_2;
	image* samuraiNapdoImg;
	image* samuraiSignImg;
	image* samuraiSkill1_E;
	image* samuraiNap_E;

	image* castleWall1;

	bool isMove;

	RECT rcFront;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void skulAnimation();
	void soldierAnimation();
	void samuraiAnimation();
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
	int getSkillCooldown1() { return skillCooldown_1; }
	int getSkillCooldown2() { return skillCooldown_2; }
	int getSkillCooldowsMax() { return CooldownMax; }
	bool getSkill1() { return skill1; }
	bool getSkill2() { return skill2; }
	
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

