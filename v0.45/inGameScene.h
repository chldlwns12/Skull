#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "player.h"
#include "map1.h"
#include "map2.h"
#include "map3.h"
#include "bossMap.h"
#include "enemy.h"
#include "progressBar.h"

class inGameScene : public gameNode
{
private:
	player* ptPlayer;
	map1* ptMap1;
	map2* ptMap2;
	map3* ptMap3;
	bossMap* ptBossMap;
	enemy* ptEnemy;
	progressBar* PlayerHpBar;
	skillCooltime* skulCoolBar1;
	skillCooltime* skulCoolBar2;
	skillCooltime* soldierCoolBar1;
	skillCooltime* samuraiCoolBar1;
	skillCooltime* samuraiCoolBar2;

	//Ÿ�� -����
	//tagTile sIngameTile[TILEX * TILEY];
	//tagTile sIngameMiniTile[TILEX * TILEY];
	//���ȭ�� ��Ʈ -����
	RECT rcIngameBg;
	image* inGameBgImg1;
	image* inGameBgImg2;
	image* inGameBgImg3;
	image* inGameBgImg4;
	//�ε�� �̹��� - ����
	image* inGameTerrainImg;
	image* inGameTerrainMiniImg;
	//image* inGameObjectImg;
	//�������� ��Ʈ - ����
	RECT rcIngameWins;
	//�̴ϸ� ��Ʈ
	RECT rcIngameMini;
	RECT rcIngameMcamera;
	image* inGameMiniBgImg1;
	image* inGameMiniBgImg2;
	image* inGameMiniBgImg3;
	image* inGameMiniBgImg4;

	image* skillCoolDown;
	image* skillCoolDown2;
	int skillCount1;
	int skillIndex1;
	int skillCount2;
	int skillIndex2;

	RECT rc[100];
	tagEnemyData sEnemyData_ingame[100];

	bool isCollision;
	float playerGravity;

	//�޴� ��Ʈ - ���� 0413
	RECT rcMenuMain;
	float menuX, menuY;
	RECT rcMenuButtonRS;	//����
	RECT rcMenuButtonOP;	//�ɼ�
	RECT rcMenuButtonQT;	//������
	bool isTouch_RS;
	bool isTouch_OP;
	bool isTouch_QT;

	bool isMenu;

	bool isRun;
	char str[100];

	bool isChange;
	bool isPlayerChange;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//void load();
	//void miniLoad();
	//void setGauge()

	inGameScene() {}
	~inGameScene() {}
};

