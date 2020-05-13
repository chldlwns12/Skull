#pragma once
#include "gameNode.h"

enum ENEMYSTATE
{
	ENEMY_IDLE = 0,
	ENEMY_RUN,
	ENEMY_HIT,
	ENEMY_ATT,
	ENEMY_DEAD
};

struct tagEnemy
{
	RECT rc;
	float enemyX, enemyY;
	image* idleImg;
	image* runImg;
	image* attImg;
	image* hitImg;
	image* deadImg;
	int count, index;
	int hp;
	int att;
	ENEMYSTATE state;
	bool isLeft;
	RECT attScope;
	bool isAtt;
};

class enemy : public gameNode
{
private:
	vector<tagEnemy> enemy;

	tagEnemy tree;
	tagEnemy soldier;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void enemyAnimation();
	void enemyScope();
	void enemyMove();
};

