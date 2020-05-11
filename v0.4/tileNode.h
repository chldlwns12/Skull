#pragma once

//게임화면 타일
#define TILESIZE 34
#define TILEX 115 // 게임화면 타일 X 크기 변경 -동주
#define TILEY 24
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

//이미지 타일(화면 우측상단에 붙여놓을 샘플타일)
#define SAMPLETILEX 15 
#define SAMPLETILEY 10

//맵툴에서 사용할 컨트롤들
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD, CTRL_DRAG,
	CTRL_TERRAIN, CTRL_OBJECT, CTRL_ERASER, CTRL_RESET, CTRL_ENEMY, //에너미 이넘 추가 -동주 
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};

//지형
enum TERRAIN
{
	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER, TR_END
};

//오브젝트
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_NONE
};

//0413 에너미데이터 구조체 추가
struct tagEnemyData
{
	long x;
	long y;
	bool isPushed;
};


//타일구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	image* img;

	tagEnemyData enemy; //0413 현구 구조체 안의 구조체 에너미데이터 추가

	bool isTouch;
	int currentEnemy;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	int enemyFrameX;
	int enemyFrameY;
};

//이미지 타일 구조체
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	int enemyFrameX;
	int enemyFrameY;
};

//에너미 타일 렉트 구조체 -동주 0410
struct tagEnemyTile
{
	RECT rcBoss;
	RECT rcGreenTurtle;
	RECT rcBlueTurtle;
	RECT rcWingTurtle;
	RECT rcDoChi;
	RECT rcMushroom;
	RECT rcGreenFlower;
	RECT rcBlueFlower;
	RECT rcGreyBird;
	RECT rcRedBird;
	RECT rcGreenBird;
	RECT rcGreyBean;
	RECT rcBlackBean;
	RECT rcBlueBean;
	RECT rcRightBullet;
	RECT rcLeftBullet;
	RECT rcCannon;
};

//현재타일 구조체
struct tagCurrentTile
{
	int x, y;
};

//툴 버튼 구조체
struct tagToolButton
{
	RECT rcSave;
	RECT rcDelete;
	RECT rcReset;
	RECT rcLoad;
};

//툴박스 구조체
struct tagToolBox
{
	RECT rcBack;
	RECT rcPage;

	float width;
	float height;
	float pageWidth;
	float pageHeight;

	int selectedPage;

	int moveSpeed;

	float x;
	float y;

	bool toggle;
};

//툴버튼 구조체
struct tagToolBtn
{
	RECT rcSave;
	RECT rcEraser;
	RECT rcReset;
	RECT rcLoad;
	RECT rcTerrain;
	RECT rcObject;
	RECT rcLeftPointer;
	RECT rcRightPointer;
	RECT rcDrag;
	RECT rcPlayer;
	RECT rcEnemy;
	RECT rcExit;

	image* imaSave;
	image* imgDelete;
	image* imgReset;
	image* imgLoad;

	float width;
	float height;
};