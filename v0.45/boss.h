#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

enum BOSSSTATE
{
	BOSS_IDLE = 0,
	BOSS_ATT1,
	BOSS_ATT2,
	BOSS_ATT3,
	BOSS_DEAD
};

class player;

class boss : public gameNode
{
private:
	bullet* ptBigBullet;
	bullet* ptBullet;
	player* ptBossPlayer;
	progressBar* bossHpBar;
private:
	int bossMaxHp;
	int bossHp;
	int bossATK;

	image* body;
	image* head;
	image* handIDLEImg_L;
	image* handIDLEImg_R;
	image* mouse;
	image* att1HandImg_L;
	image* att1HandImg_R;
	image* att2HandImg_L;
	image* att2HandImg_R;
	image* att3HandImg_L;
	image* att3HandImg_R;
	image* att2HandImg_TL;
	image* att2HandImg_TR;
	image* att2Head;
	image* att2Body;
	image* att2Mouse;
	image* deadHand_L;
	image* deadHand_R;
	image* deadHead;
	image* deadBody;
	image* deadMouse;
	image* chargeEndHead;
	image* charge;
	image* groundeEfect;
	image* smallbullet;
	image* bigBullet;
	image* boom;

	RECT rcBody;
	RECT rcHead;
	RECT rcLeftHand;
	RECT rcRightHand;
	RECT rcMouse;
	RECT rcBullet;
	RECT rcBihBullet;

	RECT Coll;

	int patternCoolDown;

	float leftHandX, leftHandY;
	float rightHandX, rightHandY;
	float BodyX, BodyY;
	float HeadX, HeadY;
	float mouseX, mouseY;

	float HeadAngle;
	float BodyAngle;

	int count, index;
	int count2, index2;
	int count3, index3;

	bool start;
	bool isAttack;

	bool isStartPettern;
	int petternCount;
	int randomPattern;
	bool pettern1_left;
	bool leftHand;
	bool rightHand;
	int pettern1Count;
	bool startPattern1;
	int randomHand;

	bool startPattern2;
	int pettern2Count;
	bool Pattern2charge;
	bool Pattern2Fire;
	int fireCount;
	bool isFire;
	float BigBulletAngle;
	float BulletAngle;
	int bulletCount;

	RECT rcEfect;
	int efectIndex;
	int efectCount;
	float AtkAngle;
	bool isAttacked;
	image* skulAttEfect;
	image* soldierAttEfect;
	image* samuraiAttEfect;
	image* samuraiSkill1_E;

	BOSSSTATE bossState;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void bossAnimation();
	void bossAnimation2();
	void randomPettern();
	void pettern_1();
	void pettern_2();
	void playerBossATK();

	void setPtPlayer(player* pt) { ptBossPlayer = pt; }

	RECT getRcLeftHand() { return rcLeftHand; }
	RECT getRcRightHand() { return rcRightHand; }
	int getBossAtk() { return bossATK; }

	bullet* getBigBullet() { return ptBigBullet; }

	bool getIsAttack() { return isAttack; }
	bool getPatternStart() { return start; }
};

