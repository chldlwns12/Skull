#include "stdafx.h"
#include "map3.h"

HRESULT map3::init()
{
	backGroundImg1 = IMAGEMANAGER->findImage("백그라운드1");
	backGroundImg2 = IMAGEMANAGER->findImage("백그라운드2");
	backGroundImg3 = IMAGEMANAGER->findImage("백그라운드3");
	backGroundImg4 = IMAGEMANAGER->findImage("백그라운드4");
	object = IMAGEMANAGER->findImage("맵3_오브젝트");
	DoorImg = IMAGEMANAGER->findImage("시작문");
	F_buttonImg = IMAGEMANAGER->findImage("F상호작용");
	InputImg = IMAGEMANAGER->findImage("들어가기");


	return S_OK;
}

void map3::release()
{
}

void map3::update()
{
}

void map3::render()
{
}
