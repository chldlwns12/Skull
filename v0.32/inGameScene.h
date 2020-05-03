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

	//타일 -이준
	//tagTile sIngameTile[TILEX * TILEY];
	//tagTile sIngameMiniTile[TILEX * TILEY];
	//배경화면 렉트 -이준
	RECT rcIngameBg;
	image* inGameBgImg1;
	image* inGameBgImg2;
	image* inGameBgImg3;
	image* inGameBgImg4;
	//로드용 이미지 - 이준
	image* inGameTerrainImg;
	image* inGameTerrainMiniImg;
	//image* inGameObjectImg;
	//윈사이즈 렉트 - 이준
	RECT rcIngameWins;
	//미니맵 렉트
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

	//메뉴 렉트 - 이준 0413
	RECT rcMenuMain;
	float menuX, menuY;
	RECT rcMenuButtonRS;	//리썸
	RECT rcMenuButtonOP;	//옵션
	RECT rcMenuButtonQT;	//나가기
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

