#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "player.h"
#include "map1.h"

class inGameScene : public gameNode
{
private:
	player* ptPlayer;
	map1* ptMap1;
	//enemy* ptEnemy;

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
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//void load();
	//void miniLoad();

	inGameScene() {}
	~inGameScene() {}
};

