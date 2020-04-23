#pragma once
#include "gameNode.h"
#include "tileNode.h"

class inGameScene : public gameNode
{
private:
	//player* ptPlayer;
	//enemy* ptEnemy;

	//Ÿ�� -����
	tagTile sIngameTile[TILEX * TILEY];
	//���ȭ�� ��Ʈ -����
	RECT rcIngameBg;
	image* inGameBgImg1;
	image* inGameBgImg2;
	image* inGameBgImg3;
	image* inGameBgImg4;
	//�ε�� �̹��� - ����
	image* inGameTerrainImg;
	image* inGameObjectImg;
	//�������� ��Ʈ - ����
	RECT rcIngameWins;

	RECT rc[100];
	tagEnemyData sEnemyData_ingame[100];

	//�޴� ��Ʈ - ���� 0413
	RECT rcMenuMain;
	float menuX, menuY;
	//RECT rcMenuButtonRS;	//����
	//RECT rcMenuButtonOP;	//�ɼ�
	//RECT rcMenuButtonEX;	//����Ʈ
	//bool isTouch_RS;
	//bool isTouch_EX;

	bool isMenu;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void load();

	inGameScene() {}
	~inGameScene() {}
};

