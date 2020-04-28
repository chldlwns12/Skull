#pragma once
#include "singletonBase.h"
enum enemyCatagory
{
	BOSS,
	GREEN_TURTLE,
	BLUE_TURTLE,
	WING_TURTLE,
	DOCHI,
	MUSHROOM,
	GREEN_FLOWER,
	BLUE_FLOWER,
	GREY_BIRD,
	GREEN_BIRD,
	RED_BIRD,
	GREY_BEAN,
	BLACK_BEAN,
	BLUE_BEAN,
};

enum playerAnimation
{
	IDLE,
	WALK,
	RUN,
	JUMP,
};


struct tagEnemy
{
	enemyCatagory category;
	POINT ptStart;
};

struct tagPlayer
{
	RECT rc;
	POINT ptStart;
	playerAnimation animation;
	float x;
	float y;
	float angle;
	int width;
	int height;
	float speed;
	float jumpSpeed;

	image* imgIdle;
	image* imgWalk;
	image* imgRun;
	image* imgJump;

};


class DataManager : public singletonBase <DataManager>
{
private:
	vector<tagEnemy> vEnemy;
	tagEnemy sEnemy;
	tagPlayer sPlayerData;

public:
	HRESULT init();
	void release();

	void setEnemy(enemyCatagory _category, float x, float y);

	void setPlayerData(float x, float y);

	vector<tagEnemy> getEnemy() { return vEnemy; }

	tagPlayer getPlayerData() { return sPlayerData; }

	DataManager() {}
	~DataManager() {}
};

