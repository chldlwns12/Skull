#include "stdafx.h"
#include "DataManager.h"

HRESULT DataManager::init()
{
	//임시로 플레이어 시작위치 설정
	setPlayerData(30, WINSIZEY / 2);

	return	S_OK;
}

void DataManager::release()
{

}


void DataManager::setEnemy(enemyCatagory _category, float _x, float _y)
{
	sEnemy.category = _category;
	sEnemy.ptStart.x = _x;
	sEnemy.ptStart.y = _y;
	vEnemy.push_back(sEnemy);
}

void DataManager::setPlayerData(float _x, float _y)
{
	sPlayerData.ptStart.x = _x;
	sPlayerData.ptStart.y = _y;
}
