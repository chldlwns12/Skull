#include "stdafx.h"
#include "map3.h"

HRESULT map3::init()
{
	backGroundImg1 = IMAGEMANAGER->findImage("��׶���1");
	backGroundImg2 = IMAGEMANAGER->findImage("��׶���2");
	backGroundImg3 = IMAGEMANAGER->findImage("��׶���3");
	backGroundImg4 = IMAGEMANAGER->findImage("��׶���4");
	object = IMAGEMANAGER->findImage("��3_������Ʈ");
	DoorImg = IMAGEMANAGER->findImage("���۹�");
	F_buttonImg = IMAGEMANAGER->findImage("F��ȣ�ۿ�");
	InputImg = IMAGEMANAGER->findImage("����");


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
