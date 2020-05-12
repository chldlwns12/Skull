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
	PLAYER_DASH,
	PLAYER_START,
	PLAYER_JUMPATT,
	PLAYER_SKILL1,
	PLAYER_SKILL2,
	PLAYER_CHANGE
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


	//�÷��̾� �⺻���� - ���ݷ� ü�� ��� �߰��ؾ���
	float playerX, playerY;
	float playerSpeed;
	int attCount;
	int attIndex;
	RECT rcPlayer;
	int playerCurrentHp;
	int playerMexHp;
	//����
	float jumpSpeed;
	float gravity;
	bool isJump;
	bool isSky;
	int jumpCount;
	//����
	bool isEndAtt1;
	bool isAtt1;
	bool isAtt2;
	bool isAttCool;
	int Att1CoolDown;
	int Att2CoolDown;
	//�뽬
	int Efect1;
	int Efect2;
	int Efect3;
	int Efect4;
	int Efect5;
	bool isDash;
	//��ų
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

	int dashCount;
	int dashCooldown;

	//�浹
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
	
	//�÷��̾� ī�޶�
	//RECT rcPlayerCamera;

	bool isLeft;
	int animationCount;
	int animationIndex;

	//�Ӹ��ִ� �̹���
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
	//�Ӹ����� �̹���
	image* nonRunImg;
	image* nonIdleImg;
	image* nonJumpImg;
	image* nonDashImg;
	image* nonDashEfectImg;
	image* nonAttImg1;
	image* nonAttImg2;
	image* nonJumpAttImg;
	//�����ذ� �̹���
	image* soldierRunImg;
	image* soldierIdleImg;
	image* soldierJumpImg;
	image* soldierDashImg;
	image* soldierDashEfectImg;
	image* soldierAttImg;
	image* soldierJumpAttImg;
	image* soldierChangeImg;
	image* soldierSkillImg;

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

