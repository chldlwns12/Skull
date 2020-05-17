#pragma once
#include "gameNode.h"
#include "progressBar.h"

enum ENEMYSTATE
{
	ENEMY_IDLE = 0,
	ENEMY_RUN,
	ENEMY_HIT,
	ENEMY_ATT,
	ENEMY_ATT2,
	ENEMY_DEAD
};

enum ENEMYKIND
{
	ENEMY_TREE = 0,
	ENEMY_SOLDIER,
	ENEMY_BIGTREE,
	ENEMY_WIZARD,
	ENEMY_BIGSOLDIER,
	ENEMY_ARCHER
};

struct tagEnemy
{
	RECT rc;
	float enemyX, enemyY;
	int Width, Height;
	image* idleImg;
	image* runImg;
	image* attImg;
	image* attImg2;
	image* hitImg;
	image* deadImg;
	image* bulletImg;
	image* skulAttEfect;
	image* soldierAttEfect;
	image* samuraiAttEfect;
	image* deadEfectImg;
	image* summonEfectImg;
	image* samuraiSkill1_E;
	int count, index;
	int efectCount, efectIndex;
	int maxHp;
	int hp;
	int att;
	ENEMYSTATE state;
	ENEMYKIND kind;
	bool isLeft;
	RECT attScope;
	RECT rcAtk;
	RECT rcAtt;
	bool isAtt;
	int attY;
	int attX;
	int runY;
	int hitY;
	int deadY;
	int deadX;
	bool isAtacked;
	float AtkAngle;
	bool isDead;
	bool isEndEfect;
	bool isAttack;
	bool isSkill;
	bool isAngle;
};

class player;

class enemy : public gameNode
{
private:
	player* ptEnemyPlayer;
	//enemyHpbar* enemyHp;
private:
	vector<tagEnemy> vEnemy;
	ENEMYKIND enemyKind;

	tagEnemy tree;
	tagEnemy soldier;
	tagEnemy bigTree;
	tagEnemy bigSoldier;

	RECT rcEfect;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void enemyAnimation();
	void enemyScope();
	void enemyMove();
	void setEnemy(ENEMYKIND kind , float X, float Y, int Width, int Height);
	void playerEnemyATK();

	vector<tagEnemy> getvEnemy() { return vEnemy; }

	void setPtPlayer(player* pt) { ptEnemyPlayer = pt; }
};

